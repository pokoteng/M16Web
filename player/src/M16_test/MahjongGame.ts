import * as io from "socket.io-client";
import * as Three from "three";
import * as Assets from "./Assets";
import State from "mahjongh5/State";
import Game from "mahjongh5/Game";
import Input from "mahjongh5/input/Input";
import UIController from "./UIController";
import CommonTileList from "mahjongh5/component/tile/CommonTileList";
import * as System from "mahjongh5/System";
import { COMMAND_TYPE } from "./data/typeSM/MahjongArgs";
import ButtonKey from "mahjongh5/input/ButtonKey";
import CommandDialog from "./CommandDialog";
import DisplayDialog from "./DisplayDialog";
import EffectController from "./EffectController";
import DoorTileList from "mahjongh5/component/tile/DoorTileList";
import Text from "mahjongh5/ui/Text";
import Cube from "mahjongh5/ui/Cube";

import Timer from "mahjongh5/component/Timer";
import { Signal } from "@robotlegsjs/signals";

export default class MahjongGame extends State {
    public loadMessage = "Loading Scene";

    public game: Game;

    public door:   DoorTileList[];
    public sea:    CommonTileList[];
    public hand:   CommonTileList[];
    public flower: CommonTileList[];
    public draw:   CommonTileList;

    public commandDialog: CommandDialog;
    public displayDialog: DisplayDialog;

    public remainTile: Text;

    public timer: Timer;

    public socket: SocketIOClient.Socket;

    private onResetEvent: Signal = new Signal();

    private uiController: UIController;

    private id: number;

    private effectController: EffectController;

    private score: number[] = [0, 0, 0, 0];

    private list = ["c","d","b","o"];

    private keepMind:number[] = [];
    private keepLock = false;

    public get effect(): EffectController {
        if (!this.effectController) {
            this.effectController = new EffectController();
        }
        return this.effectController;
    }

    public get ui(): UIController {
        if (!this.uiController) {
            this.uiController = new UIController();
        }
        return this.uiController;
    }

    /**
     * 載入及初始化場景
     * 正常此function只會在loading時被呼叫一次
     * 而且這裡不是產生場景UI物件，所以不能在這建立Phaser的UI物件
     * @param progressCallback 回傳載入進度的callback function
     * @returns 此任務的Promise
     */
    public async LoadStart(progressCallback?: (progress: number) => void): Promise<void> {
        // 連線取得現在盤面資料
        if (progressCallback) {
            progressCallback(0.8);
        }
    }

    public init() {
        super.init();
    }

    public async create() {
        super.create();

        //keyboard event
        /*document.addEventListener("keydown", (event: KeyboardEvent) => {
            if (event.code === "KeyZ") {
                this.displayDialog.Show();
            }
        }, false);

        document.addEventListener("keyup", (event: KeyboardEvent) => {
            if (event.code === "KeyZ") {
                this.displayDialog.Hide();
            }
        }, false);*/

        this.ui.Input.AddButton(this.commandDialog.pon,  Input.key.command, undefined, Input.key.Pon);
        this.ui.Input.AddButton(this.commandDialog.gon,  Input.key.command, undefined, Input.key.Gon);
        this.ui.Input.AddButton(this.commandDialog.hu,   Input.key.command, undefined, Input.key.Hu);
        this.ui.Input.AddButton(this.commandDialog.ting, Input.key.command, undefined, Input.key.Ting);
        this.ui.Input.AddButton(this.commandDialog.none, Input.key.command, undefined, Input.key.None);
        this.ui.Input.AddButton(this.commandDialog.eat,  Input.key.command, undefined, Input.key.Eat);

        this.ui.Input.AddButton(this.commandDialog.pongon, Input.key.Gon, undefined, COMMAND_TYPE.COMMAND_PONGON);
        this.ui.Input.AddButton(this.commandDialog.ongon,  Input.key.Gon, undefined, COMMAND_TYPE.COMMAND_ONGON);

        this.ui.Refresh();

		this.InitGame();
		
    }

    private TileToValue(tile: string): number
    {
        let s = tile.charAt(0);
        let value = 0;

        if (s == "N") return -1;

        for (let i = 0; i < 4; i = i + 1)
        {
            if (s == this.list[i])
            {
                value = i * 9;
                break;
            }
        }
        value = value + Number(tile.charAt(1)) - 1;

        return value;
    }

    private ValueToTile(value: number): string
    {
        if (value == -1) return "None";
        return this.list[Math.floor(value / 9)] + (value % 9 + 1);
    }

    private updateText(tileSet: number[])
    {
        let tileText = "";
        const suitList = ["m", "p", "s", "z"];
        for (let i = 0 ; i < 4; i = i + 1)
        {
            let flag = 0;
            for (let j = 0 ; j < 9 ; j = j + 1)
            {
                if (i == 3 && j == 7) continue;

                for (let k = 0 ; k < tileSet[i * 9 + j]; k = k + 1)
                {
                    flag = 1;
                    tileText = tileText + (j + 1);
                }
            }
            if (flag == 1) tileText = tileText + suitList[i];
        }

        this.displayDialog.tileText[0].text = tileText;
    }

    private randomCreateTiles(num: number): number[] {
        //random 16 tiles
        this.hand[0].ClearTileList();

        let tileSet = [];
        for (let i = 0 ; i < 34 ; i = i + 1)
        {
            tileSet.push(0);
        }

        for (let j = 0; j < num; j++) {
            let newTile = Math.floor(Math.random() * 34);
            
            tileSet[newTile] = tileSet[newTile] + 1;

            this.hand[0].AddTile(this.ValueToTile(newTile));
        }
        
        this.updateText(tileSet);

        CommonTileList.update();

        return tileSet;
    }
    
    private delay(ms: number) {
        return new Promise( resolve => setTimeout(resolve, ms) );
    }

    private async ChooseCommand(): Promise<void> {
        const action = await this.ui.Input.WaitKeyUp(Input.key.command);
        //this.commandDialog.gon.enable  = false;
        if (!this.keepLock && action == Input.key.Gon) //random 16
        {
            this.randomCreateTiles(16);
            this.commandDialog.pon.enable = false;
        }
        else if (!this.keepLock && action == Input.key.Eat) //keep 5 start
        {
            this.keepLock = true;
            let keepNum = 5;
            let tileList = this.randomCreateTiles(keepNum);
            this.keepMind = tileList;
            await this.delay(5000);
            this.displayDialog.tileText[0].text = "";
            this.hand[0].ClearTileList();
            for (let i = 0 ; i < keepNum; i = i + 1)
            {
                this.hand[0].AddTile("None");
            }
            
            this.keepLock = false;
        }
        else if (!this.keepLock && action == Input.key.Pon) //confirm
        {
            let guess = [];
            for (let i = 0 ; i < 34; i = i + 1)
            {
                guess.push(0);
            }

            for (let j = 0; j < this.hand[0].tileCount; j++) {
                let value = this.TileToValue(this.hand[0].tiles[j].ID);
    
                if (value != -1)
                {
                    guess[value] = guess[value] + 1;
                }
            }

            let flag = 0;
            for (let i = 0; i < 34; i = i + 1)
            {
                if (guess[i] != this.keepMind[i])
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                this.displayDialog.tileText[0].text = "success";
            }
            else
            {
                this.updateText(this.keepMind);
                this.displayDialog.tileText[0].text = "failed!! origin tile is: " + this.displayDialog.tileText[0].text;
            }
        }

        this.commandDialog.Show();
        this.commandDialog.gon.enable = true; 
        this.commandDialog.eat.enable = true; 
        if (action == Input.key.Eat) this.commandDialog.pon.enable = true;

        CommonTileList.update();
        this.ChooseCommand();

    }

    private async TileCommand(): Promise<void> {
        const throwTile = await Promise.race([this.hand[0].getClickTileID()]);
        
        if (!this.keepLock)
        {
            let value = this.TileToValue(throwTile);

            value = value + 1; //下一張牌
            
            if (value == 34) value = -1;
    
            let newTile = this.ValueToTile(value);
    
            this.hand[0].RemoveTile(throwTile);
            this.hand[0].AddTile(newTile);
            this.hand[0].EnableAll();
    
            let tileSet = [];
            for (let i = 0 ; i < 34 ; i = i + 1)
            {
                tileSet.push(0);
            }
    
            for (let j = 0; j < this.hand[0].tileCount; j++) {
                let value = this.TileToValue(this.hand[0].tiles[j].ID);
    
                if (value != -1)
                {
                    tileSet[value] = tileSet[value] + 1;
                }
            }
    
            this.updateText(tileSet);
            CommonTileList.update();
        }

        this.TileCommand();
    }

    private InitGame() {
        this.remainTile.visible = false;
        this.displayDialog.Show();
        this.draw.ClearTileList();
        this.draw.rotateX(Math.PI * 80 / 180);
        this.draw.position.set(9 * TILE_W, -900, (BOARD_D + TILE_H) / 2);
        const map = ["x", "y"];

        this.randomCreateTiles(16);
        
        (this.hand[0].rotation as any)[map[0 % 2]] = Math.PI * 40 / 180;
        this.hand[0].position.z = (BOARD_D + TILE_D) / 2;

        //this.hand[0].DisableAll();
        this.hand[0].EnableAll();
        CommonTileList.update();

        this.ChooseCommand();
        this.TileCommand();
    }

}
