# Tibia - AutoHeal
This is a tibiabot in c++ for any version* of the game, the Bot is based on memory injection, requires knowledge about how to get player mana and life memory addresses.
*Tip you can have it through CheatEngine*.


How it works: 

Mana Pot Hotkey = 9, manapot triggered at 90% player base mana

Life Pot Hotkey = 0, lifepot triggered at 60% player base mana

Low Priority Heal Hotkey = F1, Low priority heal is triggered at 95% player base life

High Priority Heal Hotkey = F2, High priority heal is triggered at 30% player base life

When lifepot is triggered at 60% player base life, it also trigger a low priority heal

When High Priority Heal is triggered at 30% player base life, it also trigger a lifepot
