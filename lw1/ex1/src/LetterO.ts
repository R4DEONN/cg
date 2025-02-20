import {LETTER_HEIGHT, LETTER_WIDTH, numberToHexColor} from "./utils";
import {IDrawable} from "./IDrawable";

class LetterO implements IDrawable {
	render(ctx: CanvasRenderingContext2D, x: number, y: number, color: number) {
		ctx.lineWidth = LETTER_WIDTH / 4
		ctx.fillStyle = numberToHexColor(color);
		ctx.strokeStyle = numberToHexColor(color);
		ctx.beginPath();
		ctx.ellipse(x + LETTER_WIDTH / 2, y + LETTER_HEIGHT / 2, LETTER_WIDTH / 2 - ctx.lineWidth / 2, LETTER_HEIGHT / 2 - ctx.lineWidth / 2, 0, 0, 2 * Math.PI);
		ctx.closePath();
		ctx.stroke()
	}
}

export {LetterO}