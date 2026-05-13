Welcome to Open Chat
====================

Open Chat is a basic transformer architecture library that is still in development.

Quick Start
-----------

First, add the repository as a submodule.

    git submodule add https://github.com/Bean91/Open-Chat.git

Then, include the file in your code.

    #include "/include/model.hpp"

For extended documentation, please view the [docs](https://chat.openoted.com/docs) (still in development)

How does it work?
-----------------

![Transformer Architecture](https://raw.githubusercontent.com/Bean91/Open-Chat/refs/heads/main/website/src/assets/transformer_architecture.png)

Inputted text follow the architecture outlined in the image above. Each step will be gone into depth. This architecture is how many modern chatbots function.

### Tokenizing

In essence, tokenization turns a string of characters into a vector (or list of values) of integer values. A tokenizer has a set library of key (integer ID) value (token) pairs. So, if a value is recognized, it replaces that value with the key. For example, if you wanted to tokenize `Hello, World!`, one token could be `124: "Hel"`, another `347: "lo, "`, `439: "Worl"`, and `110: "d!"`. This would replace the original string with a vector (list of values) `[124, 347, 439, 110]` for use in the next steps.

### Embedding

An embedding is a long vector of floats (decimals) for a certain token. The point of turning the tokens into embeddings is to represent the meaning for the transformer to understand. Embeddings are stored in a large table, so the token `98: "Hi"` would be looked up (in the table), and would return a large list. For a basic embedding table with 5 dimensions, token 98 could be converted to `[0.3, -0.8, 0.9, 0.2, -0.1]`. This represents meaning, as similar words (hi vs hello), in a very high-dimension space, will have a very similar direction. Obviously, in larger models, the embedding dimensions will be much larger (think 1024 or 2048) to give more meaning to each token.

### Positional Encoding

$$ {PE}{(pos, 2i)} = \sin\left(\frac{pos}{10000^{2i/d_{model}}}\right) $$
$$ {PE}{(pos, 2i+1)} = \cos\left(\frac{pos}{10000^{2i/d_{model}}}\right) $$
The math equations represent a value added to each vector embedding. These values represent the position of each dimension for the model. This enables the model to understand word order. $pos$ represents the location in the phrase of each embedding. $i$ represents the individual dimensions.

### Self-Attention

Each embedding is stacked into a large matrix denoted by $X$. It then goes through this crucial layer in all transformers, self-attention. Self-attention consists of three learned weight matrices, $W_q$, $W_k$, and $W_v$. These three matrices are dot-product-ed with $X$ to create $Q$, $K$, and $V$ (all matrices with same dimensions as $X$). $$ \text{Attention}(Q, K, V) = \text{softmax}\left(\frac{QK^T}{\sqrt{d_k}}\right)V $$ The output from this formula gives the new $X$ matrix for the next layers.

### Feed-Forward Neural Network (FNN)

The $X$ matrix get fed into a standard feed-forward neural network. For each layer, there is a weight matrix $W\_l$ and a bias vector (1D matrix) $B_l$. $$ X \bullet W_l + B_l $$ The formula for each layer is shown above. This gets passed through every layer.

### Output Layer

The transformed $X$ matrix gets multiplied against the embedding table. This creates a distribution for each token. This distribution gets softmaxed to created a probability distribution, then the most probable token gets chosen.

### Ordering

When a text request is made, first the request gets tokenized into a vector of IDs. Next, for each ID, they get embedded, stacking each embedding to create the $X$ matrix. Afterwards, positional encodings are added. Then, multiple times, they get fed through self-attention and the FNNs (different weights for each iteration). Finally, they get passed through the output layer, choosing the most probable next token.

Important Notes
---------------

This was made as a school semester project (v1 at least). Also, **this is still in development. It is not complete.**

If you would like to contribute, please look at the [`GitHub Repository`](https://github.com/Bean91/Open-Chat)