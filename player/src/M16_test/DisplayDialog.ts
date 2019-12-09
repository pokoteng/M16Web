import * as Three from "three";
import Dialog, { DialogResult } from "mahjongh5/ui/Dialog";
import Game from "mahjongh5/Game";
import ScrollTextArea from "mahjongh5/ui/ScrollTextArea";
import Text from "mahjongh5/ui/Text";

export default class DisplayDialog extends Dialog {
    // public scoreLog: ScrollTextArea;
    public X:        number;
    public Y:        number;
    public anchorX:  number = 0;
    public anchorY:  number = 0;

    public tileText: Text[];

    constructor(game: Game, onCreate: (dialog: DisplayDialog) => void, show: boolean = false) {
        super(game, onCreate);
        // 強制回應、點擊背景等於按下取消、視窗關閉時不銷毀(可重用)
        this.backgroundCancel = false;
        this.destoryOnHide    = false;

        //黑色背景
        this.CreateBG(400, 50 / ASPECT, 10, 0.7);
        this.add(this.backgroundGraphics);
        this.CreateBG(900, 900 / ASPECT, 10, 0.01);
        this.add(this.backgroundGraphics);
        
        this.add(...this.tileText);
    }

    public Show(): Promise<DialogResult> {
        this.visible = true;
        // 設定dialog物件的值
        return super.Show()
            .then((result) => {
                return result;
            });
    }

    public Hide() {
        this.visible = false;
        super.Hide();
    }

    protected Create() {
        super.Create();
    }
}
