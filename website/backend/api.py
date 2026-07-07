import os
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse, JSONResponse

app = FastAPI()

origins = [
    "http://localhost:5173",
    "https://chat.openoted.com"
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/api/docs/list")
def getDocsList():
    file_path = "docslist.txt"
    if not os.path.exists(file_path):
        raise HTTPException(status_code=500, detail="Error: File didn't open")
        
    with open(file_path, "r") as file:
        lines = [line.strip() for line in file]
    print(lines)
    return JSONResponse(content=lines)

@app.get("/api/docs/{item:path}")
def getDoc(item: str):
    file_path = "/docs/"+item+".md"
    if not os.path.exists(file_path):
        raise HTTPException(status_code=500, detail="Error: File didn't open")
    with open(file_path, "r") as doc:
        return PlainTextResponse(doc.read())



    