class Trolleybus {
	constructor(
		public x: number,
		public y: number,
		public width: number,
		public height: number
	) {}

	render(ctx: CanvasRenderingContext2D) {
		//TODO: использовать трансформации
		// Кузов
		ctx.fillStyle = 'yellow';
		ctx.beginPath();
		ctx.roundRect(this.x, this.y, this.width, this.height, [10]);
		ctx.fill()
		ctx.stroke()

		ctx.fillStyle = 'red';
		ctx.fillRect(this.x + 2, this.y + 2 * this.height / 3, this.width - 4, this.height / 6);

		ctx.lineWidth = 1;
		ctx.strokeRect(this.x + this.width / 2 - 40, this.y + 20, 40, 100);
		ctx.strokeRect(this.x + this.width / 2, this.y + 20, 40, 100);

		ctx.fillStyle = 'white';
		ctx.beginPath();
		ctx.moveTo(this.x + 60, this.y + this.height);
		ctx.lineTo(this.x + 60, this.y + this.height - 20);
		ctx.lineTo(this.x + 80, this.y + this.height - 40);
		ctx.lineTo(this.x + 110, this.y + this.height - 40);
		ctx.lineTo(this.x + 130, this.y + this.height - 20);
		ctx.lineTo(this.x + 130, this.y + this.height);
		ctx.fill();
		ctx.stroke();
		ctx.fillStyle = 'black';
		const wheelRadius = 25;
		ctx.beginPath();
		ctx.arc(this.x + 95, this.y + this.height, wheelRadius, 0, Math.PI * 2);
		ctx.fill();

		// Окна
		ctx.strokeRect(this.x + 5, this.y + 20, 50, 100);
		ctx.fillStyle = 'lightblue';
		const windowWidth = 42;
		const windowHeight = this.height / 3;
		ctx.beginPath();
		ctx.roundRect(
			this.x + 8,
			this.y + 25,
			windowWidth,
			windowHeight,
			[10]
		);
		ctx.fill()
		ctx.stroke()

		// Колеса
		ctx.fillStyle = 'black';
		ctx.beginPath();
		ctx.arc(this.x + this.width - 30, this.y + this.height, wheelRadius, 0, Math.PI * 2);
		ctx.fill();

		// Токоприемники
		ctx.strokeStyle = 'black';
		ctx.lineWidth = 3;
		ctx.beginPath();
		ctx.moveTo(this.x + this.width / 4, this.y);
		ctx.lineTo(this.x + this.width / 4, this.y - 50);
		ctx.moveTo(this.x + (3 * this.width) / 4, this.y);
		ctx.lineTo(this.x + (3 * this.width) / 4, this.y - 50);
		ctx.stroke();

		// Провода
		ctx.beginPath();
		ctx.moveTo(this.x + this.width / 4, this.y - 50);
		ctx.lineTo(this.x + (3 * this.width) / 4, this.y - 50);
		ctx.stroke();
	}
}

export {Trolleybus}