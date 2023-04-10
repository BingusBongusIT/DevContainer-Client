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

In CLion muss dazu noch einmalig die Docker Toolchain konfiguriert werden.  
[Weiter Infos zur Docker Toolchain](https://blog.jetbrains.com/clion/2021/10/clion-2021-3-eap-new-docker-toolchain/)
1. Öffne *Einstellungen | Build, Execution, Deployment | Toolchains*.
2. Füge eine neue Toolchain vom Docker Type hinzu.
3. Wähle als Image *CPP-DevContainer* aus.
4. Öffne benötigte Ports in den Container Einstellungen
5. *(Optional)* Die Docker Toolchain als erste setzen damit sie die Standard Toolchain ist.

Nachdem diese Voraussetzungen erfüllt sind kann dieses Repository in CLion als neues Projekt geklont werden.
Nun kann die App weiterentwickelt werden.
