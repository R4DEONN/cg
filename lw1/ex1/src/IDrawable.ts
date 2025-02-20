interface IDrawable {
	render(ctx: CanvasRenderingContext2D, x: number, y: number, color: number): void;
}

export {IDrawable};