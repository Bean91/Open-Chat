import { useEffect } from "react";
import Navbar from "./Navbar.tsx";
import { useTitle } from "./hooks/useTitle.ts";
import 'github-markdown-css/github-markdown-dark.css';
import transformer_architecture from './assets/transformer_architecture.png';

declare global {
	interface Window {
		MathJax: any;
	}
}

function Home() {
	useTitle("Home | Open Chat");
	useEffect(() => {
		window.MathJax = {
			tex: {
				inlineMath: [['$', '$'], ['\\(', '\\)']],
				displayMath: [['$$', '$$'], ['\\[', '\\]']]
			},
			startup: {
				typeset: false
			}
		};

		const typeset = () => window.MathJax?.typesetPromise?.();
		const existing = document.getElementById('mathjax-script') as HTMLScriptElement | null;

		if (existing) {
			if (window.MathJax?.typesetPromise) {
				typeset();
			} else {
				existing.addEventListener('load', typeset);
			}
			return;
		}

		const script = document.createElement('script');
		script.id = 'mathjax-script';
		script.src = 'https://cdn.jsdelivr.net/npm/mathjax@4/tex-mml-chtml.js';
		script.async = true;
		script.onload = typeset;
		document.head.appendChild(script);
	}, []);

	return (
		<div className="bg-gray-500 min-h-screen text-white" id="root">
			<Navbar location={"Home"} />
			<div className="mt-16 bg-gray-500"></div>
			<div className="bg-gray-500">
				<article className="markdown-body p-4 min-h-[calc(100vh-4rem)] h-fit">
					<h1>Welcome to Open Chat</h1>
					<p>Open Chat is a basic transformer architecture library that is still in development.</p>

					<h2>Quick Start</h2>
					<p>First, add the repository as a submodule.</p>
					<pre><code className="language-bash">git submodule add https://github.com/Bean91/Open-Chat.git</code></pre>
					<p>Then, include the file in your code.</p>
					<pre><code className="language-cpp">#include "/include/model.hpp"</code></pre>
					<p>For extended documentation, please view the <a href="https://chat.openoted.com/docs">docs</a> (still in development)</p>

					<h2>How does it work?</h2>
					<p><img alt="Transformer Architecture" src={transformer_architecture} className="bg-black w-1/4 mx-auto" /></p>
					<p>Inputted text follow the architecture outlined in the image above. Each step will be gone into depth. This architecture is how many modern chatbots function.</p>

					<h3>Tokenizing</h3>
					<p>In essence, tokenization turns a string of characters into a vector (or list of values) of integer values. A tokenizer has a set library of key (integer ID) value (token) pairs. So, if a value is recognized, it replaces that value with the key. For example, if you wanted to tokenize <code>Hello, World!</code>, one token could be <code>124: "Hel"</code>, another <code>347: "lo, "</code>, <code>439: "Worl"</code>, and <code>110: "d!"</code>. This would replace the original string with a vector (list of values) <code>[124, 347, 439, 110]</code> for use in the next steps.</p>

					<h3>Embedding</h3>
					<p>An embedding is a long vector of floats (decimals) for a certain token. The point of turning the tokens into embeddings is to represent the meaning for the transformer to understand. Embeddings are stored in a large table, so the token <code>98: "Hi"</code> would be looked up (in the table), and would return a large list. For a basic embedding table with 5 dimensions, token 98 could be converted to <code>[0.3, -0.8, 0.9, 0.2, -0.1]</code>. This represents meaning, as similar words (hi vs hello), in a very high-dimension space, will have a very similar direction. Obviously, in larger models, the embedding dimensions will be much larger (think 1024 or 2048) to give more meaning to each token.</p>

					<h3>Positional Encoding</h3>
					<p>
						{"$$ PE_{(pos, 2i)} = \\sin\\left(\\frac{pos}{10000 ^ { 2i / d_{model}}}\\right) $$"}
						{"$$ PE_{(pos, 2i+1)} = \\cos\\left(\\frac{pos}{10000 ^ { 2i / d_{model}}}\\right) $$"}

						The math equations represent a value added to each vector embedding. These values represent the position of each dimension for the model. This enables the model to understand word order. $pos$ represents the location in the phrase of each embedding. $i$ represents the individual dimensions.</p>

					<h3>Self-Attention</h3>
					<p>
						Each embedding is stacked into a large matrix denoted by $X$. It then goes through this crucial layer in all transformers, self-attention. Self-attention consists of three learned weight matrices, $W_q$, $W_k$, and $W_v$. These three matrices are dot-product-ed with $X$ to create $Q$, $K$, and $V$ (all matrices with same dimensions as $X$).
						{"$$ \\text{Attention}(Q, K, V) = \\text{softmax}\\left(\\frac{QK ^ T}{\\sqrt{d_k}}\\right)V $$"}
						The output from this formula gives the new $X$ matrix for the next layers.</p>

					<h3>Feed-Forward Neural Network (FNN)</h3>
					<p>The $X$ matrix get fed into a standard feed-forward neural network. For each layer, there is a weight matrix $W_l$ and a bias vector (1D matrix) $B_l$.
						{"$$ X * W_l + B_l $$"}
						The formula for each layer is shown above. This gets passed through every layer.</p>

					<h3>Output Layer</h3>
					<p>The transformed $X$ matrix gets multiplied against the embedding table. This creates a distribution for each token. This distribution gets softmaxed to created a probability distribution, then the most probable token gets chosen.</p>

					<h3>Ordering</h3>
					<p>When a text request is made, first the request gets tokenized into a vector of IDs. Next, for each ID, they get embedded, stacking each embedding to create the $X$ matrix. Afterwards, positional encodings are added. Then, multiple times, they get fed through self-attention and the FNNs (different weights for each iteration). Finally, they get passed through the output layer, choosing the most probable next token.</p>

					<h2>Important Notes</h2>
					<p>This was made as a school semester project (v1 at least). Also, <b>this is still in development. It is not complete.</b></p>
					<p>If you would like to contribute, please look at the <a href="https://github.com/Bean91/Open-Chat"><code>GitHub Repository</code></a></p>
				</article>
			</div>

		</div>
	);
}

export default Home;
