import * as Three from "three";
import * as io from "socket.io-client";
import * as Mahjongh5 from "mahjongh5/Mahjongh5";
import Game from "mahjongh5/Game";
import JoinState from "./JoinState";
import MahjongGame from "./MahjongGame";
import RoundEdgedBox from "mahjongh5/Util/RoundBoxGeometry";
import CommonTileList from "mahjongh5/component/tile/CommonTileList";
import ImageTileTable from "mahjongh5/component/tile/ImageTileTable";
import DoorTileList from "mahjongh5/component/tile/DoorTileList";
import ChoseLackDialog from "./ChoseLackDialog";
import CommandDialog from "./CommandDialog";
import Button from "mahjongh5/ui/Button";
import * as Assets from "./Assets";
import Text from "mahjongh5/ui/Text";
import Timer from "mahjongh5/component/Timer";
import NumberDisplayer from "mahjongh5/ui/NumberDisplayer";
import Cube from "mahjongh5/ui/Cube";
import DiceEffect from "./effect/DiceEffect";
import RoundRetangleGeometry from "mahjongh5/Util/RoundRectangleGeometry";
import DisplayDialog from "./displayDialog";

export default function MahjongStart() {
    let isPlaying = false;

    const init = (game: Game) => {
        game.assets     = Assets;

        const mahjong   = new MahjongGame(game);

        game.gameStates.push(mahjong);

        game.loadState.onCreate.add(() => {
            const scene  = new Three.Scene();
            const camera = new Three.PerspectiveCamera(50, game.sceneWidth / game.sceneHeight, 0.1, 3000);

            game.loadState.scene.push(scene);
            game.loadState.camera.push(camera);
        });

        mahjong.onCreate.add(() => {
            const scene  = new Three.Scene();
            const camera = new Three.PerspectiveCamera(50, game.sceneWidth / game.sceneHeight, 0.1, 5000);

            const w = 1000;
            const h = w / ASPECT;
            const orthoScene  = new Three.Scene();
            const orthoCamera = new Three.OrthographicCamera(-w / 2, w / 2, h / 2, -h / 2, -1000, 1000);

            const diceScene  = new Three.Scene();
            const diceCamera = new Three.OrthographicCamera(-w / 2, w / 2, h / 2, -h / 2, -1000, 1000);

            scene.background = new Three.Color(0xAAAAAA);

            camera.position.set(0, -1800, 1500);
            camera.rotateX(0.8);

            const ambientLight = new Three.AmbientLight(0xA0A0A0);
            scene.add(ambientLight);

            const pointLight = new Three.PointLight(0x070707, 15);

            pointLight.position.set(0, -2000, 1000);
            pointLight.lookAt(0, 0, 0);
            scene.add(pointLight);

            const outBoardW = 2200;
            const outBoardH = 100;
            const halfOutW  = outBoardW / 2;
            const halfOutH  = outBoardH / 2;
            const geometry  = new Three.Geometry().fromBufferGeometry(RoundEdgedBox(outBoardW, outBoardH, 150, 30, 1, 1, 1, 5));
            const geometry2 = geometry.clone();
            const geometry3 = geometry.clone();
            const geometry4 = geometry.clone();
            geometry.translate(0, -halfOutW + halfOutH, 0);
            geometry2.translate(0, halfOutW - halfOutH, 0);
            geometry2.rotateZ(Math.PI / 2);
            geometry3.translate(0,  halfOutW - halfOutH, 0);
            geometry4.translate(0, -halfOutW + halfOutH, 0);
            geometry4.rotateZ(Math.PI / 2);
            geometry.merge(geometry2);
            geometry.merge(geometry3);
            geometry.merge(geometry4);
            geometry.mergeVertices();
            const material = new Three.MeshLambertMaterial({ color: 0xA38511 });
            const outBoard = new Three.Mesh(geometry, material);
            scene.add(outBoard);

            const board = new Three.Mesh(new Three.BoxBufferGeometry(BOARD_W, BOARD_H, 100), new Three.MeshLambertMaterial({ color: 0x0B440C }));
            scene.add(board);

            // arrow setting
            const sideLen1 = 60;
            const sideLen2 = 60;
            const angle    = 90;
            const height   = 10;
            const shape = new Three.Shape();
            let x = 0;
            let y = 0;
            shape.moveTo(x, y);
            x += sideLen1;
            shape.lineTo(x, y);
            x -= sideLen2 * Math.cos(Math.PI * angle / 180);
            y += sideLen2 * Math.sin(Math.PI * angle / 180);
            shape.lineTo(x, y);
            shape.lineTo(0, 0);

            const extrudeSettings = {
                depth:          height,
                bevelEnabled:   true,
                bevelThickness: 1,
                bevelSize:      8,
                bevelSegments:  1,
            };

            const tileTable = new ImageTileTable(game, game.cache[Assets.tiles.tiles_config.key], Assets.tiles.tiles.key, Assets.tiles.tilesJson.key);
            CommonTileList.Init(TILE_W, TILE_H, TILE_D, TILE_R, tileTable);

            const hand   = [];
            //設定寬度
            hand.push(new CommonTileList(game, 16, TILE_W, TILE_H, TILE_D, true, 16, true));
            const draw = new CommonTileList(game, 0, TILE_W, TILE_H, TILE_D, true);

            // hand
            hand[0].rotateX(Math.PI);
            new Three.Box3().setFromObject(hand[0]).getCenter(hand[0].position).multiplyScalar(-1);
            hand[0].position.y = -900;
            hand[0].position.z = (BOARD_D + TILE_D) / 2;

            CommonTileList.intersectsScene.add(...hand);
            CommonTileList.intersectsScene.add(draw);

            const timer = new Timer(new NumberDisplayer(new Text(game, "0", Assets.font.jhengHei.key, 80 , 20, new Three.MeshLambertMaterial({ color: 0xFFFFFF }), 0, 0, 50, true)), undefined, DISABLE_TINT);
            scene.add(timer);

            const diceEffect = new DiceEffect(game);
            diceScene.add(diceEffect);

            const commandDialog = new CommandDialog(game, (dialog: CommandDialog) => {
                const buttonGeometry = new Three.CircleGeometry(50, 30);

                const eatTex    = new Three.Texture(game.cache[Assets.button.eat.key]);
                const ponTex    = new Three.Texture(game.cache[Assets.button.pon.key]);
                const gonTex    = new Three.Texture(game.cache[Assets.button.gon.key]);
                const huTex     = new Three.Texture(game.cache[Assets.button.hu.key]);
                const tingTex   = new Three.Texture(game.cache[Assets.button.ting.key]);
                const ongonTex  = new Three.Texture(game.cache[Assets.button.ongon.key]);
                const pongonTex = new Three.Texture(game.cache[Assets.button.pongon.key]);
                const noneTex   = new Three.Texture(game.cache[Assets.button.none.key]);
                eatTex.needsUpdate    = true;
                ponTex.needsUpdate    = true;
                gonTex.needsUpdate    = true;
                huTex.needsUpdate     = true;
                tingTex.needsUpdate   = true;
                ongonTex.needsUpdate  = true;
                pongonTex.needsUpdate = true;
                noneTex.needsUpdate   = true;

                dialog.eat    = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: eatTex }));
                dialog.pon    = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: ponTex }));
                dialog.gon    = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: gonTex }));
                dialog.hu     = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: huTex }));
                dialog.ting   = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: tingTex }));
                dialog.ongon  = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: ongonTex }));
                dialog.pongon = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: pongonTex }));
                dialog.none   = new Button(game, buttonGeometry, new Three.MeshLambertMaterial({ map: noneTex }));

                dialog.eat.position.x = -385;
                dialog.eat.position.z = 2;
                dialog.eat.stateTint.down    = DOWN_TINT;
                dialog.eat.stateTint.disable = DISABLE_TINT;
                dialog.pon.position.x = -275;
                dialog.pon.position.z = 2;
                dialog.pon.stateTint.down    = DOWN_TINT;
                dialog.pon.stateTint.disable = DISABLE_TINT;                
                dialog.gon.position.x = -165;
                dialog.gon.position.z = 2;
                dialog.gon.stateTint.down    = DOWN_TINT;
                dialog.gon.stateTint.disable = DISABLE_TINT;
                dialog.hu.position.x = -55;
                dialog.hu.position.z = 2;
                dialog.hu.stateTint.down    = DOWN_TINT;
                dialog.hu.stateTint.disable = DISABLE_TINT;
                dialog.ting.position.x = 55;
                dialog.ting.position.z = 2;
                dialog.ting.stateTint.down    = DOWN_TINT;
                dialog.ting.stateTint.disable = DISABLE_TINT;
                dialog.ongon.position.x = 165;
                dialog.ongon.position.z = 2;
                dialog.ongon.stateTint.down    = DOWN_TINT;
                dialog.ongon.stateTint.disable = DISABLE_TINT;
                dialog.pongon.position.x = 275;
                dialog.pongon.position.z = 2;
                dialog.pongon.stateTint.down    = DOWN_TINT;
                dialog.pongon.stateTint.disable = DISABLE_TINT;
                dialog.none.position.x = 385;
                dialog.none.position.z = 2;
                dialog.none.stateTint.down    = DOWN_TINT;
                dialog.none.stateTint.disable = DISABLE_TINT;
            });

            const remainTile = new Text(game, "剩餘張數: ", Assets.font.jhengHei.key, 40, 1, new Three.MeshLambertMaterial({ color: 0x000000 }), -1200, 600, 300);
            remainTile.visible = false;

            const group = new Three.Group();
            group.rotation.setFromVector3(camera.rotation.toVector3());
            group.add(commandDialog);
            group.add(remainTile);
            commandDialog.position.set(600, -700, 850);
            commandDialog.Show();
            commandDialog.gon.enable = true; //random 16
            commandDialog.eat.enable = true; //start keep
            //commandDialog.pon.enable = true; //confirm
            
            //顯示commandDialog -> commandDialog.Show();
            //仿照Dialog系列作出自己的UI
            scene.add(group);

            const instanceTlies = new Three.Mesh(CommonTileList.instancedGeometry, CommonTileList.rawShaderMaterial);
            scene.add(instanceTlies);

            const displayDialog = new DisplayDialog(game, (dialog: DisplayDialog) => {

                dialog.tileText   = [];

                dialog.tileText.push(new Text(game, "",    Assets.font.jhengHei.key, 15, 1, new Three.MeshBasicMaterial({ color: 0xFFFFFF }), 0, 0, 0, false));

                dialog.tileText[0].PosX = -135;
                dialog.tileText[0].PosY = -h / 2 + 300;

            });
            displayDialog.visible    = false;
            displayDialog.position.z = 10;

            orthoScene.add(displayDialog);

            //mahjong.socket = socket;

            mahjong.remainTile = remainTile;

            mahjong.hand   = hand;
            mahjong.draw   = draw;

            mahjong.effect.diceEffect = diceEffect;

            mahjong.timer = timer;

            mahjong.commandDialog = commandDialog;
            mahjong.displayDialog = displayDialog;

            mahjong.scene.push(scene);
            mahjong.camera.push(camera);
            mahjong.scene.push(diceScene);
            mahjong.camera.push(diceCamera);
            mahjong.scene.push(orthoScene);
            mahjong.camera.push(orthoCamera);
        });
    };

	Mahjongh5.StartGame(init, "game");
}