import {drawLine, LETTER_HEIGHT, LETTER_WIDTH, numberToHexColor} from "./utils";
import {IDrawable} from "./IDrawable";

class LetterB implements IDrawable {
	render(ctx: CanvasRenderingContext2D, x: number, y: number, color: number) {
		ctx.lineWidth = LETTER_WIDTH / 4
		ctx.fillStyle = numberToHexColor(color);
		ctx.strokeStyle = numberToHexColor(color);
		let currentX = x;
		let currentY = y;
		let currentWidth = LETTER_WIDTH / 3;
		let currentHeight = LETTER_HEIGHT;
		drawLine(ctx,  x, y, LETTER_HEIGHT, Math.PI / 2)
		currentWidth = 2 * LETTER_WIDTH / 3;
		currentHeight = LETTER_HEIGHT / 4;
		currentY += currentHeight;
		ctx.beginPath();
		ctx.ellipse(currentX, currentY, currentWidth, currentHeight - LETTER_WIDTH / 8, Math.PI, Math.PI / 2, 3 * Math.PI / 2);
		currentY += currentHeight * 2;
		ctx.ellipse(currentX, currentY, currentWidth, currentHeight - LETTER_WIDTH / 8, Math.PI, Math.PI / 2, 3 * Math.PI / 2);
		ctx.closePath();
		ctx.stroke()
	}
}

export {LetterB}