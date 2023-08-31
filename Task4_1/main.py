# File: main.py
# Author: Ziad Mohamed Elsayed
# Description: Simulates a battle between Gru and Vector using weapons and shields.
# Date: 8/23

from Villain import Gru, Vector
from Gadgets import *

def simulate_battle():
    round_num = 1

    # Battle loop continues until one villain's health reaches zero or both run out of energy
    while gru.health > 0 and vector.health > 0:
        print(f"Round {round_num}")

        # Villains choose their actions
        gru_action = gru.choose_action()
        vector_action = vector.choose_action()

        # Handle shield actions
        if isinstance(gru_action, Shield) and gru_action.apply_shield(gru):
            print(f"Gru uses {gru_action.name} shield.")
        
        if isinstance(vector_action, Shield) and vector_action.apply_shield(vector):
            print(f"Vector uses {vector_action.name} shield.")

        # Handle weapon actions
        if isinstance(gru_action, Weapon) and gru_action.attack(gru, vector):
            print(f"Gru attacks Vector with {gru_action.name}.")
        
        if isinstance(vector_action, Weapon) and vector_action.attack(vector, gru):
            print(f"Vector attacks Gru with {vector_action.name}.")

        # Display current health and energy status
        print(f"Gru health: {gru.health}, Vector health: {vector.health}")
        print(f"Gru energy: {gru.energy}, Vector energy: {vector.energy}\n")
        round_num += 1 # increment number of rounds

        # Check if both villains have run out of energy
        if gru.energy < 20 and vector.energy < 15:
            print("Both villains have run out of energy. The battle ends in a draw.")
            break

    # Determine the winner based on health
    if gru.health <= 0:
        print("Vector wins!")
    else:
        print("Gru wins!")

# Initialize Gru and Vector
gru = Gru()
vector = Vector()

if __name__ == "__main__":
    simulate_battle()
