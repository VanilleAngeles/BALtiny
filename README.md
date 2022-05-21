# BALtiny - Supervision d'une boîte aux lettres
## Besoin
Ma boîte aux lettres est éloignée de la maison, le facteur passe rarement et surtout de manière irrégulière (heure variable). La plupart du temps j'allais relever le courrier ... dans une boîte vide et quand j'oubliais, un courrier important m'attendait depuis plusieurs jours.
## Ébauche d'un projet
Un ami (Roger P) m'avait fait un montage électronique à base d'émetteur 433Mhz activé dans la boîte aux lettres par une bascule reliée au volet de la boîte, émetteur qui communiquait avec un récepteur dans la maison pour allumer une *Led* remise à son état initial par un bouton *Reset*. Mais la fragilité du montage (humidité dans la boîte) et son coût (couple émetteur/récepteur assez chers) ont définitivement scellé la mort de ce montage.
## Un montage simple et efficace
Qu'à cela ne tienne, la youtubeuse Heliox nous a fourni un montage tout simple à base de sonnette externe [Lien](https://youtu.be/WknRG6paMcA); un interrupteur à mercure (ou à bille) bascule à l'ouverture du volet, ce qui fait sonner le carillon à l'intérieur. Mon ami Roger P m'a fait un montage tout simple et ça fonctionnait. Le facteur passe, il dépose du courrier, ça sonne.
Mais la fonction essentielle pour moi qui consiste à garder trace du passage du facteur (donc quand on n'est pas là) n'était pas assurée. Raison pour laquelle je suis passé à un montage plus élaboré ... et moins cher que le tout premier.
## Le projet définitif
### Matériel
Une sonnette avec bouton poussoir et surtout ampoule/*Led* sur le récepteur quand le bouton est actionné (en effet il est plus simple de détecter une lumière qui s'allume plutôt qu'une tension sur une carte électronuqe dont on n'a pas le schéma). J'ai préféré une sonnette autonome sur pile pour ne pas avoir à risquer un court-circuit si je me trompais entre les différents voltages (15€).  
Un chargeur de téléphone 5v (récupération) pour remplacer les 3 piles 1,5v.  
Une carte breadboard mini format à souder (1€ pièce).  
Un contrôleur ATtiny 45 (4€).  
Des résistances, un interrupteur à bille, de la soudure et une résistance photovoltaïque (on dit 3 €).  
Total max 25€.
### Le fonctionnement
1. Sur soulèvement du volet de dépose courrier ou ouverture de la porte de la boîte aux lettres, le bouton poussoir est actionné par l'interrupteur à bille/mercure qui est sur une bascule.
2. Le récepteur sonne et sa *Led*/ampoule s'allume. La résistance photovoltaïque détecte la lumière et transmet l'information au contrôleur ATtiny qui était à l'écoute.
3. Le contrôleur allume la *Led* et passe à l'écoute du bouton *Reset* du boitier
4. Dès le *Reset* est activé, l'ATtiny repasse à l'écoute de la résistance photovoltaïque.
### Option
J'ai ajouté trois fils à la sortie du boîtier sonnette pour communiquer avec un Raspberry. En effet l'ATtiny ne sait pas envoyer des informations sur le réseau. Donc une paire de fils sortent du 5v et la masse pour alimenter le Raspberry et le + de la *Led* du boîtier sonnette permet de signaler au Raspberry que la *Led* est allumée. Ainsi, par un programme Python des plus simple, si le *Reset* n'est pas activé dans le quart d'heure (paramétrable), un message est envoyé sur Smartphone. Cette fonction est très utile si un voisin/ami est en charge de relever votre courrier pendant votre absence.
## Déconvenues
1. Pour l'alimentation du Raspberry et du boitier sonnette, prévoir un chargeur suffisamment puissant pour alimenter les deux (sinon le boîtier sonnette ne perçoit pas l'activation du bouton externe)
2. Il faut isoler de la lumière extérieure l'ampoule/*Led* du boitier sonnette (et donc la résistance photovolatique) pour éviter qu'une exposition du boîtier sonnette au soleil ou à la lumière artificielle intérieure ne lui fasse croire que le facteur est passé.
3. Je n'ai pas calculé la consommation totale ATtiny + raspberry mais ça ne devrait pas aller bien loin d'autant plus qu'un raspberry PI Zero suffit amplement (et vous pouvez l'utiliser pour autre chise d'ailleurs)... Si on utilise le seul contrôleur Attiny (sans Raspberry), la consommation est négligeable (entre 1mA et 5mA). Et dans ce montage on économise les piles du récepteur dans le boîtier sonnette (et la place des piles est utilisée pour mettre le montage électronique).
4. Si la distance entre la boîte aux lettres et le boîtier sonnette est importante, il faudra veiller à utiliser un matériel qui a une portée suffisante
5. J'ai mis mon bouton sonnette à l'extérieur de la boîte aux lettres pour limiter la place prise par le dispositif dans la boîte (cas de dépose de colis) et surtout pour pouvoir l'étanchéifier (je l'ai mis dans une boite étanche même si le bouton est étanche par construction) et pour remplacer la pile plus facilement.
## la mise en place
Bien sûr il faut programmer le contrôleur ATtiny 45 avec l'interface IDE de l'Arduino. Comme c'est un peu compliqué, je donne la référence de ce qu'il faut faire.[Lien](https://youtu.be/S-oBujsoe-Q).  
Ensuite il faut soritr le fer à souder; ce dépôt inclut le schéma du montage au format standard Fritzing. J'en mets ici une copie d'écran (il est à noter que je n'y ai pas mis la sortie optionnelle vers le Raspberry, il lui faut du 5v, de la masse et la sorite + vers la diode.
![Montage électronique](https://github.com/VanilleAngeles/BALtiny/blob/master/IMG_1212.png)
## Conclusion
Quand je suis chez moi, je suis averti dès que quelqu'un dépose quelque chose dans la boîte aux lettres (bien utile quand on attend une livraison).  
Quand je suis absent et que je rentre le soir, je sais si il y a eu un dépôt pendant mon absence.  
Si je demande à quelqu'un de relever mon courrier, il peut en être averti sur son smartphone (mais ça oblige à lui laisser l'accès au bouton *Reset* du boîtier sonnette qui est souvent à l'intérieur).  
Donc prochain développement: permettre de faire un *Reset* à distance (avec un Raspberry qui monte une *pin* du port GPIO pour le dire à l'ATtiny ça ne devrait pas poser trop de problème).
## Annexes
### Montage électronique (dans boîtier sonnette)
![Boîtier électronique](https://github.com/VanilleAngeles/BALtiny/blob/master/IMG_1209.jpg)
### Interrupteur à bille dans boîte aux lettres
![Interrupteur à bille](https://github.com/VanilleAngeles/BALtiny/blob/master/IMG_1210.jpg)
### Boîtier sonnette avec *Led* allumée, bouton *Reset* dessous et 3 fils qui peuvent aller sur un Raspberry
![Boîtier sonnette](https://github.com/VanilleAngeles/BALtiny/blob/master/IMG_1211.jpg)


 


