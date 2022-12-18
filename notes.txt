# Planning

## Program Flow
1. Show start page GUI and enable selecting project, maybe port.
2. After program started, host flutter app on port via http.
3. Listen for keyboard commands over tcp
4. If GUI stop button is pressed, kill server

## Desktop GUI
Contains:
* Start page:
  * Directory select box to select location of flutter project build
    * Could save last used project
    * Could have list of projects that have been used before. Automatically add once ran, but able to delete with button.
  * Button to start server
* Running page:
  * Text showing url where app can be used.
  * Button to stop server

## Resources
* [Medium Article about HTTP over TCP](https://medium.com/swlh/looking-under-the-hood-http-over-tcp-sockets-952a944c99da)
