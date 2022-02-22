# plotjuggler_asservstream_plugin

Ce plugin plotjuggler permet de lire les infos de l'asserv sortant sur le port USB et d'afficher les données en temps réel sur plotjuggler !

## Avant de compiler

Il faut initialiser le sous module de plotjuggler:

```
git submodule update --init
```

Il va falloir la lib config pour le C++

```
sudo apt install libconfig++-dev
```

## compiler plotjuggler

```
cd PlotJuggler
mkdir build
cd build
cmake ..
make
```


## compiler le plugin asserv_stream

```
cd asserv_stream_plugin
mkdir build
cd build
cmake -DPlotJuggler_LIBRARY:FILEPATH="../../PlotJuggler/build"  -DPlotJuggler_INCLUDE_DIR:FILEPATH="../../PlotJuggler/plotjuggler_base/include/PlotJuggler"  ..
make
```


Voir le repo du plugin pour ce qui est nécéssaire pour la compilation et l'utilisation de plotjuggler : https://github.com/facontidavide/PlotJuggler


## utiliser le plugin

Dans plotjuggler, il faudra ajouter le dossier où vous avez compilez le plugin.
Dans "App"  --> préférences --> plugin --> add plugin folders  :
```
plotjuggler_asservstream_plugin/asserv_stream_plugin/build
```

Il faudra rebooter plotjuggler pour que le plugin soit dispo dans la liste des streaming à gauche.
