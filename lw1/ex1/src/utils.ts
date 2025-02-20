function numberToHexColor(number: number): string {
	if (number < 0 || number > 16777215) {
		throw new Error("Число должно быть в диапазоне от 0 до 16777215");
	}

	const hex = number.toString(16).padStart(6, '0');

	return `#${hex}`;
}

function drawLine(ctx: CanvasRenderingContext2D, x1: number, y1: number, length: number, angle: number) {
	const x2 = x1 + length * Math.cos(angle); // Конечная точка X
	const y2 = y1 + length * Math.sin(angle); // Конечная точка Y

	ctx.beginPath();
	ctx.moveTo(x1, y1);
	ctx.lineTo(x2, y2);
	ctx.stroke();
}

const LETTER_WIDTH = 80;
const LETTER_HEIGHT = 120;


export {numberToHexColor, LETTER_HEIGHT, LETTER_WIDTH, drawLine};