import {IDrawable} from "./IDrawable";
import {LETTER_WIDTH} from "./utils";

class Scene {
	private _objects: IDrawable[];
	private _phase: number = 0;

	constructor(...objects: IDrawable[]) {
		this._objects = objects;
	}

	render(ctx: CanvasRenderingContext2D, centerX: number, centerY: number, width: number, height: number) {
		ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);

		let currentX = centerX - width / 2;
		const startY = centerY - height / 2;

		//TODO: Сделать по физическим законам
		this._objects.forEach((obj, index) => {
			const offsetY = Math.sin(this._phase + index * 0.5) * 20;
			obj.render(ctx, currentX, startY + offsetY, 0x000000);
			currentX += LETTER_WIDTH + 20;
		});

		this._phase += 0.05;
		requestAnimationFrame(() => this.render(ctx, centerX, centerY, width, height));
	}
}

export {Scene};