import {drawLine, LETTER_HEIGHT, LETTER_WIDTH, numberToHexColor} from "./utils";
import {IDrawable} from "./IDrawable";

class LetterK implements IDrawable {
	render(ctx: CanvasRenderingContext2D, x: number, y: number, color: number) {
		ctx.lineWidth = LETTER_WIDTH / 4
		ctx.fillStyle = numberToHexColor(color);
		// ctx.fillRect(x, y, LETTER_WIDTH / 3, LETTER_HEIGHT);

		drawLine(ctx, x, y, LETTER_HEIGHT, Math.PI / 2)
		drawLine(ctx, x + 10, y + LETTER_HEIGHT / 2, LETTER_HEIGHT / 1.6, 7 * Math.PI / 4)
		drawLine(ctx, x + 10, y + LETTER_HEIGHT / 2, LETTER_HEIGHT / 1.6, Math.PI / 4)
	}
}

export {LetterK}