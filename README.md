# Cub3D

test merge





#### Not in order

⚠️ *"Error\n" if any misconfiguration of any kind **IN the file**, **FOLLOWED** by an explicit message of your choice*

> Décision prise: **retour d'erreur avec errno** pour les checks de droits/existence des fichiers/retour_des_fonctions utilisées dans le parsing, du moment que ce n'est pas une erreur de formatage de la scene

### Parsing road-map

- [x] program parameter validity

##### Informations part
- [x] check textures directions format
- [x] check textures files rights
- [x] check floor/ceiling values
- [ ] check functions calls
- [ ] errno set

##### Map part
- [ ] Check possible characters inside map
- [ ] Check floodfill
- [ ] Check closed map




### Informations dump

- [unsigned char (colors)](https://stackoverflow.com/questions/5742967/why-unsigned-char-for-rgb-pixel-data)
- [unsigned char (geekforgeeks)](https://www.geeksforgeeks.org/unsigned-char-in-c-with-examples/)
