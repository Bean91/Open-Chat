import './style.css';
import { Routes, Route } from 'react-router';
import Home from "./Home.tsx";
import Docs from "./Docs.tsx";
import NotFound from "./NotFound.tsx";

function App() {
	return (
		<div>
			<Routes>
				<Route path={"/"} element={<Home />} />
				<Route path={"/docs"} >
					<Route index element={<Docs section={false} item={false} />} />
        			<Route path="aiusage" element={<Docs section={true} item={false} />} />
        			<Route path=":section/:item" element={<Docs section={true} item={true} />} />
				</Route>
				<Route path={"*"} element={<NotFound />} />
			</Routes>
		</div>
	)
}

export default App;