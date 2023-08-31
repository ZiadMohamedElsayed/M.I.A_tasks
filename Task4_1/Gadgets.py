# File: Gadgets.py
# Author: Ziad Mohamed Elsayed
# Description: Contains Gadget, Weapon, and Shield classes, along with gadget instances.
# Date: 8/23

# Base class for all gadgets
class Gadget:
    def __init__(self, name, energy, resource =100):
        self.name = name
        self.energy = energy
        self.resource = resource

# Weapon class, inheriting from Gadget
class Weapon(Gadget):
    def __init__(self, name, energy, damage, resource=100):
        super().__init__(name, energy, resource)
        self.damage = damage

    # Attack method for weapons
    def attack(self, attacker, villain):

        # Check if the weapon has any resource left
        if self.resource <= 0:
            print(f"{attacker.name} doesn't have more {self.name}")
            return False
        
        # Check if the attacker has enough energy to use the weapon
        if attacker.energy < self.energy:
            print(f"{villain.name} doesn't have enough energy for this Weapon.")
            return False
        

        attacker.energy -= self.energy  # Deduct energy cost from the attacker
        self.resource -= 1              # Decrease the weapon's resource by 1
        
        # Remove the weapon from attacker's weapons list if resource is depleted
        if self.resource <= 0:
            attacker.weapons.remove(self)

        # Calculate damage based on villain's shield (except for 'Kalman Missile')
        if villain.shield > 0 and self.name != 'Kalman Missile':
            currDamage = self.damage * (1 - villain.shield)
        else:
            currDamage = self.damage
        
        villain.health -= currDamage    # Deduct calculated damage from the villain's health
        
        # Ensure villain's health doesn't go below zero
        if villain.health < 0:
            villain.health = 0

        return True

# Shield class, inheriting from Gadget
class Shield(Gadget):
    def __init__(self, name, energy, save, resource = 100):
        super().__init__(name, energy, resource)
        self.save = save

    # Apply shield method for shields
    def apply_shield(self, villain):

        # Check if the shield has any resource left
        if self.resource <= 0:
            print(f"{villain.name} doesn't have more {self.name}")
            return False
        
        # Check if the villain has enough energy to activate the shield
        if villain.energy < self.energy:
            print(f"{villain.name} doesn't have enough energy for this shield.")
            return False

        
        villain.shield = self.save      # Apply the shield's saving value to the villain's shield
        villain.energy -= self.energy   # Deduct energy cost from the villain
        self.resource -= 1              # Decrease the shield's resource by 1

        return True


# Define instances of weapons and shields
FreezeGun = Weapon('Freeze Gun', 50, 11)
ElectricProd = Weapon('Electric Prod', 88, 18, 5)
MegaMagnet = Weapon('Mega Magnet', 92, 10, 3)
KalmanMissile = Weapon('Kalman Missile', 120, 20, 1)

EnergyProjectedBarrierGun = Shield('Energy-Projected BarrierGun', 20, 0.4)
SelectivePermeability = Shield('Selective Permeability', 50, 0.9, 2)

LaserBlasters = Weapon('Laser Blasters', 40, 8)
PlasmaGrenades = Weapon('Plasma Grenades', 56, 13, 8)
SonicResonanceCannon = Weapon('Sonic Resonance Cannon', 100, 22, 3)

EnergyNetTrap = Shield('Energy Net Trap', 15, 0.32)
QuantumDeflector = Shield('Quantum Deflector', 40, 0.8, 3)