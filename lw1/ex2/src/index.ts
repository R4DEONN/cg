import {Trolleybus} from "./Trolleybus";

class App {
	private canvas: HTMLCanvasElement;
	private ctx: CanvasRenderingContext2D;
	private trolleybus: Trolleybus;
	private isDragging: boolean = false;
	private offsetX: number = 0;
	private offsetY: number = 0;

	constructor() {
		this.canvas = document.getElementById('canvas') as HTMLCanvasElement;
		this.canvas.width = window.outerWidth;
		this.canvas.height = window.outerHeight;
		this.ctx = this.canvas.getContext('2d')!;
		this.trolleybus = new Trolleybus(200, 200, 500, 150);

		this.canvas.addEventListener('mousedown', this.onMouseDown.bind(this));
		this.canvas.addEventListener('mousemove', this.onMouseMove.bind(this));
		this.canvas.addEventListener('mouseup', this.onMouseUp.bind(this));

		this.render();
	}

	private render() {
		this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
		this.trolleybus.render(this.ctx);
		requestAnimationFrame(() => this.render());
	}

	private onMouseDown(e: MouseEvent) {
		const rect = this.canvas.getBoundingClientRect();
		const mouseX = e.clientX - rect.left;
		const mouseY = e.clientY - rect.top;

		if (
			mouseX >= this.trolleybus.x &&
			mouseX <= this.trolleybus.x + this.trolleybus.width &&
			mouseY >= this.trolleybus.y &&
			mouseY <= this.trolleybus.y + this.trolleybus.height
		) {
			this.isDragging = true;
			this.offsetX = mouseX - this.trolleybus.x;
			this.offsetY = mouseY - this.trolleybus.y;
		}
	}

	private onMouseMove(e: MouseEvent) {
		if (this.isDragging) {
			const rect = this.canvas.getBoundingClientRect();
			const mouseX = e.clientX - rect.left;
			const mouseY = e.clientY - rect.top;

			this.trolleybus.x = mouseX - this.offsetX;
			this.trolleybus.y = mouseY - this.offsetY;
		}
	}

	private onMouseUp() {
		this.isDragging = false;
	}
}

new App();