// consensus_demo.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void simulatePoW() {
    int power1 = rand() % 100;
    int power2 = rand() % 100;
    cout << "🔹 PoW Simulation:\n";
    cout << "Miner A Power: " << power1 << "\n";
    cout << "Miner B Power: " << power2 << "\n";
    cout << "✅ Selected: " << ((power1 > power2) ? "Miner A" : "Miner B") << " (Higher computational power)\n";
}

void simulatePoS() {
    int stake1 = rand() % 1000;
    int stake2 = rand() % 1000;
    cout << "\n🔹 PoS Simulation:\n";
    cout << "Staker A Stake: " << stake1 << "\n";
    cout << "Staker B Stake: " << stake2 << "\n";
    cout << "✅ Selected: " << ((stake1 > stake2) ? "Staker A" : "Staker B") << " (Higher token stake)\n";
}

void simulateDPoS() {
    int votes[3] = {rand() % 10, rand() % 10, rand() % 10};
    int maxVote = *max_element(votes, votes + 3);

    cout << "\n🔹 DPoS Voting Simulation:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Delegate " << i + 1 << ": " << votes[i] << " votes\n";
    }

    for (int i = 0; i < 3; ++i) {
        if (votes[i] == maxVote) {
            cout << "✅ Selected: Delegate " << i + 1 << " (Most votes)\n";
            break;
        }
    }
}

int main() {
    srand(time(0));
    cout << "\n Consensus Mechanism Demonstration:\n";

    simulatePoW();
    simulatePoS();
    simulateDPoS();

    return 0;
}
