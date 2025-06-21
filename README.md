# Cub3D

Un moteur de ray-casting 3D inspiré de Wolfenstein 3D, développé en C avec des fonctionnalités avancées d'optimisation et d'immersion.

## 📋 Table des matières

- [Description](#description)
- [Fonctionnalités](#fonctionnalités)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Compilation](#compilation)
- [Utilisation](#utilisation)
- [Structure du projet](#structure-du-projet)
- [Tests](#tests)
- [Fonctionnalités bonus](#fonctionnalités-bonus)
- [Optimisations](#optimisations)
- [Contributeurs](#contributeurs)

## 🎮 Description

Cub3D est un moteur de rendu 3D utilisant la technique du ray-casting pour créer une expérience visuelle immersive similaire aux premiers jeux FPS comme Wolfenstein 3D. Le projet inclut un système de gestion de cartes, un moteur de rendu optimisé, un système audio intégré et une interface utilisateur avec HUD.

## ✨ Fonctionnalités

### Version Mandatory
- **Moteur de ray-casting** : Rendu 3D en temps réel avec projection de rayons
- **Parsing de cartes** : Lecture et validation de fichiers de cartes .cub
- **Textures murales** : Support des textures XPM pour les murs (Nord, Sud, Est, Ouest)
- **Couleurs de sol et plafond** : Configuration personnalisable via les fichiers de carte
- **Contrôles joueur** : Déplacement WASD et rotation avec les flèches ou la souris
- **Gestion des collisions** : Détection des murs et limites de carte

### Version Bonus
- **HUD avancé** : Interface utilisateur avec jauge de carburant et informations de jeu
- **Minimap** : Carte miniature en temps réel montrant la position du joueur
- **Système de portes** : Portes interactives avec animations d'ouverture/fermeture
- **Collectibles** : Objets à ramasser (potions)
- **Système audio** : Sons d'ambiance et effets sonores avec MiniAudio
- **Effets visuels** : Brouillard, torche, éclairage dynamique
- **Multithreading** : Optimisation des performances avec traitement parallèle
- **Monstres** : Entités IA basiques (en développement)

## 🔧 Prérequis

### Système d'exploitation
- **Linux** (Ubuntu/Debian recommandé)
- **macOS** (avec Xcode Command Line Tools)

### Dépendances système
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y make gcc xorg libxext-dev libx11-dev zlib1g-dev libbsd-dev libxrandr-dev x11proto-dev

# macOS
xcode-select --install
```

### Dépendances incluses
- **libft** : Bibliothèque C personnalisée (incluse)
- **MLX (MiniLibX)** : Bibliothèque graphique (auto-téléchargée)
- **MiniAudio** : Bibliothèque audio (incluse dans le code)

## 📦 Installation

1. **Cloner le repository**
```bash
git clone https://github.com/NotMiniRT/Cub3D cub3d
cd cub3d
```

2. **Initialiser les submodules**
```bash
git submodule update --init --recursive
```

## 🔨 Compilation

### Version mandatory
```bash
make
```

### Version bonus
```bash
make bonus
```

### Options de compilation
```bash
make debug          # Compilation avec symboles de debug
make debugb         # Compilation bonus avec debug
make clean          # Nettoyer les fichiers objets
make fclean         # Nettoyer complètement
make re             # Recompiler entièrement
```

## 🚀 Utilisation

### Lancement du jeu
```bash
./cub3D [fichier_de_carte.cub]
```

### Exemple
```bash
./cub3D assets/mandatory/maps/valid_map.cub
```

### Contrôles

#### Version mandatory
- **W/A/S/D** : Déplacement
- **←/→** : Rotation de la caméra
- **ESC** : Quitter le jeu

#### Version bonus
- **W/A/S/D** : Déplacement
- **Souris** : Rotation de la caméra
- **E** : Interagir avec les portes
- **ESC** : Quitter le jeu

### Format des cartes

Les fichiers `.cub` doivent contenir :
```
NO ./assets/textures/north_wall.xpm
SO ./assets/textures/south_wall.xpm
WE ./assets/textures/west_wall.xpm
EA ./assets/textures/east_wall.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Légende :
- `0` : Espace vide
- `1` : Mur
- `N/S/E/W` : Position et orientation initiale du joueur
- `D` : Porte (bonus)
- `C` : Collectible (potions, bonus)

## 📁 Structure du projet

```
cub3d/
├── srcs/
│   ├── mandatory/          # Code version obligatoire
│   │   ├── display/        # Rendu et affichage
│   │   ├── parsing/        # Analyse des cartes
│   │   └── utils/          # Utilitaires
│   └── bonus/              # Code version bonus
│       ├── display/        # Rendu avancé
│       ├── parsing/        # Parsing étendu
│       ├── threads/        # Multithreading
│       └── sound/          # Système audio
├── incs/                   # Headers
├── assets/                 # Ressources du jeu
│   ├── mandatory/maps/     # Cartes version obligatoire
│   ├── bonus/maps/         # Cartes version bonus
│   └── textures/           # Textures et sprites
├── libft/                  # Bibliothèque C personnalisée
├── mlx/                    # MiniLibX (submodule)
├── scripts/                # Scripts de test
├── .github/workflows/      # CI/CD automatisée
└── Makefile               # Configuration de compilation
```

## 🧪 Tests

### Tests automatisés
Le projet inclut une suite de tests automatisés via GitHub Actions :

```bash
# Tests de compilation
make

# Tests de cartes valides
./scripts/test_correct_maps.sh

# Tests de cartes invalides
./scripts/test_map_errors.sh

# Tests avec Valgrind (détection de fuites mémoire)
./scripts/test_map_errors_valgrind.sh
```


## 🎯 Fonctionnalités bonus

### Interface utilisateur avancée
- **Jauge de carburant** : Système de carburant limitant la distance de vision
- **Minimap temps réel** : Affichage de la carte avec position du joueur
- **HUD interactif** : Informations de jeu en surimpression

### Mécaniques de jeu
- **Portes interactives** : Ouverture/fermeture avec animations
- **Système de collectibles** : Potions et objets à ramasser
- **Éclairage dynamique** : Torche avec effets de lumière

### Optimisations techniques
- **Multithreading** : Traitement parallèle pour améliorer les performances
- **Cache de textures** : Optimisation de la gestion mémoire
- **Rendu optimisé** : Techniques d'optimisation du ray-casting

## ⚡ Optimisations

### Performances
- **Compilation optimisée** : Flags `-O3` pour les performances
- **Cache de calculs** : Précalcul des tables trigonométriques
- **Gestion mémoire** : Allocation/libération optimisées
- **Multithreading** : Parallélisation des calculs intensifs

### Techniques de rendu
- **DDA Algorithm** : Digital Differential Analyzer pour le ray-casting
- **Texture mapping** : Mapping optimisé des textures sur les murs
- **Culling** : Élimination des calculs inutiles
- **Distance correction** : Correction de l'effet "fish-eye"

## 🏗️ Architecture technique

### Moteur de ray-casting
Le cœur du projet utilise l'algorithme DDA (Digital Differential Analyzer) pour calculer les intersections des rayons avec les murs. Chaque rayon est projeté depuis la position du joueur selon l'angle de vue, permettant de calculer la distance aux murs et de déterminer la hauteur des colonnes à afficher.

### Gestion des textures
Les textures sont chargées au format XPM et stockées en mémoire pour un accès rapide. Le système de mapping de textures calcule les coordonnées en fonction de la position d'intersection du rayon avec le mur.

### Système audio
L'intégration de MiniAudio permet la lecture de sons d'ambiance et d'effets sonores, avec support de multiple formats audio et gestion du positionnement spatial.

## 🤝 Contributeurs

agantaum && gueberso
