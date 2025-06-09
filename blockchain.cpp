// blockchain.cpp
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <chrono>
#include "picosha2.h"

using namespace std;

class Block {
public:
    int index;
    string timestamp;
    string data;
    string previousHash;
    string hash;
    int nonce;

    Block(int idx, string data, string prevHash) {
        index = idx;
        this->data = data;
        previousHash = prevHash;
        nonce = 0;
        timestamp = getCurrentTime();
        hash = calculateHash();
    }

    string calculateHash() const {
        string input = to_string(index) + timestamp + data + previousHash + to_string(nonce);
        return picosha2::hash256_hex_string(input);
    }

    string getCurrentTime() const {
        time_t now = time(0);
        return ctime(&now);
    }

    void mineBlock(int difficulty) {
        string prefix(difficulty, '0');
        auto start = chrono::high_resolution_clock::now();

        while (hash.substr(0, difficulty) != prefix) {
            nonce++;
            hash = calculateHash();
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "⛏️ Mined Block " << index << " in " << nonce << " attempts";
        cout << " (⏱️ " << elapsed.count() << " seconds)\n";
        cout << "✅ Hash: " << hash << "\n";
    }

    void displayBlock() const {
        cout << "\n--- Block " << index << " ---\n";
        cout << "Timestamp     : " << timestamp;
        cout << "Data          : " << data << endl;
        cout << "Previous Hash : " << previousHash << endl;
        cout << "Hash          : " << hash << endl;
    }
};

int main() {
    vector<Block> blockchain;
    int difficulty = 4;

    Block genesis(0, "Genesis Block", "0");
    genesis.mineBlock(difficulty);
    blockchain.push_back(genesis);

    Block block1(1, "Block 1 data", blockchain.back().hash);
    block1.mineBlock(difficulty);
    blockchain.push_back(block1);

    Block block2(2, "Block 2 data", blockchain.back().hash);
    block2.mineBlock(difficulty);
    blockchain.push_back(block2);

    cout << "\n✅ Final Blockchain:\n";
    for (Block& b : blockchain) {
        b.displayBlock();
    }

    cout << "\n⚠️ Tampering Block 1...\n";
    blockchain[1].data = "Hacked Data!";
    blockchain[1].hash = blockchain[1].calculateHash();

    cout << "\n❌ Blockchain After Tampering:\n";
    for (Block& b : blockchain) {
        b.displayBlock();
    }

    cout << "\n🔍 NOTICE: Block 2's previous hash doesn't match Block 1's new hash!\n";

    return 0;
}
