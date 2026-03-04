import json;
from datasets import load_dataset;

english = True;
french = True;
code = False;
file_limit = 10000
current_batch = [];
current_size = 0;
min_size_bytes = 10240;

if (english): #{
    file_count = 0;
    ds = load_dataset("nampdn-ai/mini-en", split="train");
    for row in ds: #{
        row_json = json.dumps(row["text"]);
        row_size = len(row_json.encode('utf-8'));
        
        current_batch.append(row_json);
        current_size += row_size;
        
        if (file_count >= file_limit):
            break;
        
        if (current_size >= min_size_bytes): #{
            filename = f"training_corpus/english/file{file_count:03d}.txt";
            
            with open(filename, "w") as f: #{
                json.dump("\n\n".join(current_batch), f);
            #}
            
            file_count += 1;
            current_batch = [];
            current_size = 0;
        #}
    #}
#}

if (french): #{
    file_count = 0;
    ds = load_dataset("MaxLSB/LeCarnet", split="train");
    replacements = {
        r'\\u00e9': 'é',
        r'\\u00e0': 'à',
        r'\\u00e8': 'è',
        r'\\u00e7': 'ç',
        r'\\u00f9': 'ù',
        r'\\u00ea': 'ê',
        r'\\u00ee': 'î',
        r'\\u00ef': 'ï',
        r'\\u00f4': 'ô',
        r'\\u00fb': 'û',
        r'\\u00e2': 'â',
        r'\\u00eb': 'ë',
    }
    for row in ds: #{
        row_json = json.dumps(row["text"]);
        for old, new in replacements.items():
            row_json = row_json.replace(old, new)
        row_size = len(row_json.encode('utf-8'));
    
        current_batch.append(row_json);
        current_size += row_size;
        
        if (file_count >= file_limit):
            break;
        
        if (current_size >= min_size_bytes): #{
            filename = f"training_corpus/french/file{file_count:03d}.txt";
    
            with open(filename, "w") as f: #{
                json.dump("\n\n".join(current_batch), f);
            #}
    
            file_count += 1;
            current_batch = [];
            current_size = 0;
        #}
    #}
#}

if (code): #{
    # ds = load_dataset("MaxLSB/LeCarnet", split="train");
    file_count = 3;
    for row in ds: #{
        row_json = json.dumps(row["text"]);
        row_size = len(row_json.encode('utf-8'));

        current_batch.append(row_json);
        current_size += row_size;

        if (current_size >= min_size_bytes): #{
            filename = f"training_corpus/code/file{file_count:03d}.txt";

            with open(filename, "w") as f: #{
                json.dump("\n\n".join(current_batch), f);
            #}

            file_count += 1;
            current_batch = [];
            current_size = 0;
        #}
    #}
#}