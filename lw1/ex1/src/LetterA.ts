import {drawLine, LETTER_HEIGHT, LETTER_WIDTH, numberToHexColor} from "./utils";
import {IDrawable} from "./IDrawable";

class LetterA implements IDrawable {
	//TODO: Убрать цвет и сделать красивой
	render(ctx: CanvasRenderingContext2D, x: number, y: number, color: number) {
		y += LETTER_HEIGHT
		ctx.lineWidth = LETTER_WIDTH / 4;
		drawLine(ctx, x, y, LETTER_HEIGHT, 8 * Math.PI / 5);
		drawLine(ctx, x + 15, y - LETTER_HEIGHT / 3, LETTER_WIDTH - 30, 0);
		drawLine(ctx, x + LETTER_WIDTH - 8, y, LETTER_HEIGHT, 7 * Math.PI / 5);
	}
}

export {LetterA}