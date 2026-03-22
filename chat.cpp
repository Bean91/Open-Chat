#include <string>
#include <vector>
#include <iostream>
#include "llama.h"

float * embed(std::string input) {
    llama_model_params mparams = llama_model_default_params();
    llama_model * model = llama_model_load_from_file("nomic-embed-text-v1.5.Q2_K.gguf", mparams);
    
    llama_context_params cparams = llama_context_default_params();
    cparams.embeddings = true;
    llama_context * ctx = llama_init_from_model(model, cparams);
    
    std::vector<llama_token> tokens(512);
    const llama_vocab* vocab = llama_model_get_vocab(model);
    int n = llama_tokenize(vocab, input.c_str(), input.size(), tokens.data(), 512, true, false);
    tokens.resize(n);
    
    llama_batch batch = llama_batch_get_one(tokens.data(), tokens.size());
    llama_decode(ctx, batch);
    
    return llama_get_embeddings(ctx);
}

int main() {
    std::string input;
    std::cin >> input;
    float * embedded = embed(input);
}