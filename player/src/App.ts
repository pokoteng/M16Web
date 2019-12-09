import "./index.html";
import "./game.html";
import "./room.html";
import "./counting.html";
import "./training.html";
import "./defence.html";
import "./tools.html";
import Mahjong from "./M16";
import Mtest from "./M16_test";

var count = 2;
if (count == 1) window.onload = Mahjong;
else window.onload = Mtest;