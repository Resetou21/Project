# Manuel d'utilisation des touches

## 1. Fermeture de la fenêtre
- **Touche** : Échapper (Esc) ou X dans la barre de titre
- **Action** : Ferme la fenêtre et supprime tous les fichiers de sortie générés pendant la simulation.

## 2. Contrôle de la simulation
- **Touche** : Espace
- **Action** : Met en pause ou reprend la simulation. Un message "Jeu mis en pause" sera affiché lorsque le jeu est en pause.

## 3. Placement des cellules
- **Touche** : O
  - **Action** : Place un obstacle à la position de la souris lorsque vous cliquez avec le bouton gauche.
  
- **Touche** : V
  - **Action** : Place une cellule vivante à la position de la souris lorsque vous cliquez avec le bouton gauche.

## 4. Modification des paramètres
- **Touche** : I
  - **Action** : Permet de modifier le temps d'écart entre les itérations de la simulation. Après avoir appuyé sur **I**, entrez un nouveau délai en millisecondes via le clavier.

## 5. Placement de motifs prédéfinis
- **Touche** : Numpad1
  - **Action** : Place le motif "Loaf" à la position de la souris. Ce motif est un oscillateur.
  
- **Touche** : Numpad2
  - **Action** : Place le motif "Toad" à la position de la souris. Ce motif est également un oscillateur.
  
- **Touche** : Numpad3
  - **Action** : Place le motif "Beacon" à la position de la souris. Ce motif est un oscillateur qui change de forme entre deux états.

## 6. Implémentation du Glider
- **Action** : Cliquez avec le bouton de la souris pour placer un glider à la position de la souris. Un message "Glidder implémenté" sera affiché dans la console.

## Autres Informations
- **Entrée de l'utilisateur** : Au démarrage, le programme demande à l'utilisateur d'entrer le nombre d'itérations pour la simulation.
- **Affichage** : La grille est mise à jour et redessinée à chaque itération, et les fichiers d'itération sont sauvegardés dans un dossier nommé "output".

## Conseils d'utilisation
- Assurez-vous d'avoir **SFML** correctement installé pour exécuter le programme.
- Utilisez les touches numériques du pavé numérique pour un placement facile des motifs prédéfinis.
- Modifiez le paramètre d'écart judicieusement pour observer différentes vitesses de simulation.
