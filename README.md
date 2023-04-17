# CChat-Server

C++ Client für eine kleine Chat-Applikation, welche für das Modul 347 über Docker erstellt wurde.

## Starten


## Entwickeln

Um dieses Projekt weiterzuentwickeln werden Git, Docker und CLion benötigt.

Für die Kompilierung und das Starten der Applikation wird dieses Image benötigt [colllijo/cpp-devcontainer](https://hub.docker.com/r/colllijo/cpp-devcontainer).
Die neueste Version des Images kann mit diesem Befehl geladen werden:
```bash
docker pull colllijo/cpp-devcontainer:latest
```

In CLion muss dazu noch einmalig für jedes Projekt die Docker Toolchain konfiguriert werden. Dazu kann in CLion ein neues Projekt
durch das Klonen des Repositorys erstellten werden. Falls nun in der CMake Konsole ein Fehler erscheint, dass keine Konfiguration
gefunden werden kann, muss der Konfigurieren-Knopf gedrückt werden und die CMakeLists.txt Datei gewählt werden.
Daraufhin kann der DevContainer folgendermassen konfiguriert werden kann:
1. Öffne *Settings | Build, Execution, Deployment | Toolchains*.
2. Füge eine neue Toolchain vom Docker Type hinzu.
3. Wähle als Image *CPP-DevContainer* aus.
4. Öffne benötigte Ports in den Container Einstellungen.
5. Öffne *Settings | Build, Execution, Deployment | CMake*.
6. Hier zwei Profile über den + Knopf erstellen eines mit Build Type Release und eines mit Debug.
7. Für beide Profile die zuvor erstellte Docker Toolchain auswählen.
8. Den Build Ordner auf <<ProjektVerzeichnis>>/out/release und <<ProjektVerzeichnis>>/out/debug setzen. 

[Weiter Infos zur Docker Toolchain](https://blog.jetbrains.com/clion/2021/10/clion-2021-3-eap-new-docker-toolchain/)
