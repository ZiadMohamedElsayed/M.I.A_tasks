# File: Villain.py
# Author: Ziad Mohamed Elsayed
# Description: Contains Gru and Vector classes.
# Date: 8/23

import random
from Gadgets import *

# Base class for all villains
class Villain:
    def __init__(self, name, health = 100, energy = 500, shield = 0):
        self.name = name
        self.health = health
        self.energy = energy
        self.shield = shield

    # Method to choose an action (to be overridden by subclasses)
    def choose_action(self):
        pass
# Gru class, inheriting from Villain
class Gru(Villain):
    def __init__(self):
        super().__init__("Gru")
        self.weapons = [FreezeGun, ElectricProd, MegaMagnet, KalmanMissile]
        self.shields = [EnergyProjectedBarrierGun, SelectivePermeability]

    # Method to choose an action for Gru
    def choose_action(self):
        # Check if Gru's energy is too low to take any more actions
        if self.energy < 20:
            print(f"{self.name} has run out of energy and can't make any more actions.")
            return None
        
        self.shield = 0

        while True:
            print("Choose your action:")
            print("1. Use weapon")
            print("2. Use shield")
            try:
                choice = int(input("\nEnter the number of your choice: "))
                if choice == 1:
                    return self.choose_weapon()
                elif choice == 2:
                    return self.choose_shield()
                else:
                    print("Invalid choice. Please choose 1 or 2.")
            except ValueError:
                print("Invalid input. Please enter a number.")

    # Method to choose a weapon for Gru
    def choose_weapon(self):
        while True:
            print("Choose a weapon:")
            print(f"1. Freeze Gun ∞")
            print(f"2. Electric Prod {ElectricProd.resource}")
            print(f"3. Mega Magnet {MegaMagnet.resource}")
            print(f"4. Kalman Missile {KalmanMissile.resource}")
            
            try:
                choice = int(input("\nEnter the number of your choice: "))
                if choice == 1:
                    return FreezeGun
                elif choice == 2:
                    return ElectricProd
                elif choice == 3:
                    return MegaMagnet
                elif choice == 4:
                    return KalmanMissile
                else:
                    print("Invalid choice. Please choose 1, 2, 3, or 4.")
            except ValueError:
                    print("Invalid input. Please enter a number.")

    # Method to choose a shield for Gru
    def choose_shield(self):
        while True:
            print("Choose a shield:")
            print(f"1. Energy-Projected BarrierGun ∞")
            print(f"2. Selective Permeability {SelectivePermeability.resource}")

            try:
                choice = int(input("\nEnter the number of your choice: "))
                if choice == 1:
                    return EnergyProjectedBarrierGun
                elif choice == 2:
                    return SelectivePermeability
                else:
                    print("Invalid choice. Please choose 1 or 2.")
            except ValueError:
                print("Invalid input. Please enter a number.")
        
# Vector class, inheriting from Villain
class Vector(Villain):
    def __init__(self):
        super().__init__("Vector")
        self.weapons = [LaserBlasters, PlasmaGrenades, SonicResonanceCannon]
        self.shields = [EnergyNetTrap, QuantumDeflector]

    # Method to choose an action for Vector
    def choose_action(self):
        # Check if Vector's energy is too low to take any more actions
        if self.energy <= 0:
            print(f"{self.name} has run out of energy and can't make any more actions.")
            return None
        
        choice = random.choice(["weapon", "shield"])
        if choice == "weapon":
            return self.choose_weapon()
        elif choice == "shield":
            return self.choose_shield()

    # Method to choose a random weapon for Vector
    def choose_weapon(self):
        return random.choice(self.weapons)

    # Method to choose a random shield for Vector
    def choose_shield(self):
        return random.choice(self.shields)