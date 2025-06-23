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
- **Cache de calculs** : Précalcul des tables trigonométriques
- **Gestion mémoire** : Allocation/libération optimisées
- **Multithreading** : Parallélisation des calculs intensifs

### Techniques de rendu
- **DDA Algorithm** : Digital Differential Analyzer pour le ray-casting
- **Texture mapping** : Mapping optimisé des textures sur les murs
- **Culling** : Élimination des calculs inutiles
- **Distance correction** : Correction de l'effet "fish-eye"

## 🏗️ Architecture technique

### Fonctionnement du ray-casting (DDA)
Le moteur utilise l'algorithme DDA (Digital Differential Analyzer) pour effectuer la projection de rayons à partir de la position du joueur, en fonction de sa direction (calculée via cos(θ) et sin(θ)). Chaque rayon progresse dans la carte grille par grille, en testant à chaque itération s'il entre en collision avec un mur, un objet, une porte ou un monstre.

Le DDA permet ainsi de détecter très rapidement l'obstacle le plus proche dans une direction donnée, ce qui permet d'afficher une colonne de pixels proportionnelle à la distance calculée. Les entités dynamiques telles que les portes et les monstres, ou fixes comme les objets ramassables (collectibles), sont également intégrées dans cette logique de détection. À chaque rayon, une vérification est effectuée pour savoir si une entité se trouve dans le champ du joueur, puis cette information est utilisée lors du rendu.

### Optimisations techniques internes
Plusieurs optimisations ont été mises en place pour améliorer les performances du moteur :

**Pré-calculs mathématiques** : Toutes les valeurs trigonométriques non dynamiques sont pré-calculées. Seuls les cos et sin des rayons à tracer restent calculés en temps réel pour garantir un affichage fluide.

**Textures en mémoire optimisée** : Les images (textures murales, objets, HUD) sont volontairement pivotées sur le côté au chargement afin de permettre un accès par colonne verticale (très utile pour le ray-casting), en simplifiant l'accès mémoire par ligne dans un tableau.

### Expérimentations graphiques
Ce projet a également été un terrain d'expérimentation graphique :

**Objets fixes** : Affichés avec une perspective simple.

**Collectibles** : Affichés indépendamment du joueur ; ils ne réagissent pas à la direction du regard, mais à la distance et tournent sur eux-mêmes.

**Monstre dynamique** : Une entité mobile qui fait toujours face au joueur et est affichée face au joueur.

**Portes interactives** : Gèrent leur animation d'ouverture via un état interne déclenché par une interaction du joueur (E).

**Effets d'obscurité** : Plusieurs méthodes sont combinées pour créer une ambiance sombre :
- Réduction dynamique de la luminosité du mur selon la distance
- Réduction progressive de la luminosité du sol en fonction de la distance avec le joueur
- Réduction uniforme de la luminosité du plafond
- Le tout relié à une valeur qui fluctue dans le code, représentée par la jauge de carburant

### Gestion des textures
Les textures sont chargées au format XPM et stockées en mémoire pour un accès rapide. Le système de mapping de textures calcule les coordonnées UV en fonction de la position d'intersection du rayon avec le mur.

### Système audio
L'intégration de MinIAudio permet la lecture de sons d'ambiance et d'effets sonores, avec support de multiples formats audio et gestion du positionnement spatial.
## 🤝 Contributeurs

agantaum && gueberso
