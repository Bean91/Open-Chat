import Navbar from "./Navbar.tsx";
import { useTitle } from "./hooks/useTitle.ts";

function NotFound() {
	useTitle("404 | Open Render");

	return (
		<div>
			<Navbar location={"Not Found"} />
			<div className={"flex items-center text-center justify-center h-[calc(100vh-4rem)] mt-16 bg-gray-500"}>
				<div className={"text-center"}>
					<h1 className={"text-[12rem] text-white"}>404</h1>
					<p className={"text-xl text-white"}>Page not found</p>
					<a className={"text-xl text-blue-400 cursor-pointer"} href={"/"}>Home</a>
				</div>
			</div>
		</div>
	)
}

export default NotFound;