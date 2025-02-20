import {LetterB} from "./LetterB";
import {Scene} from "./Scene";
import {LetterO} from "./LetterO";
import {LetterK} from "./LetterK";
import {LetterA} from "./LetterA";

function main() {
	const canvas = document.getElementById("canvas") as HTMLCanvasElement;
	canvas.width = window.outerWidth
	canvas.height = window.outerHeight

	const ctx = canvas.getContext("2d") as CanvasRenderingContext2D;

	const scene = new Scene(new LetterB, new LetterK, new LetterA);

	scene.render(ctx, canvas.width / 2, canvas.height / 2, 200, 100);
}

main();