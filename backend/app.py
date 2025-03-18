import requests
from typing import Final
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

ESP_IP: Final[str] = "http://192.168.8.122"

app: FastAPI = FastAPI()
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/led/{state}")
async def control_led(state: str) -> dict[str, str]:
    if state.upper() not in ['ON', 'OFF']:
        return {"error": "Invalid state. 'ON' or 'OFF' only"}
    response = requests.get(f"{ESP_IP}/led?state={state.upper()}")
    return {"message": response.text}
