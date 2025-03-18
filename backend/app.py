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


@app.get("/led/all/{state}")
async def control_all_leds(state: str) -> dict[str, str]:
    if state.upper() not in ['ON', 'OFF']:
        return {"error": "Invalid state. 'ON' or 'OFF' only"}
    response: requests.Response = requests.get(f"{ESP_IP}/led/all?state={state.upper()}")
    return {"message": response.text}


@app.get("/led/pattern/{state}")
async def toggle_display_led_pattern(state: str) -> dict[str, str]:
    if state.upper() not in ['ON', 'OFF']:
        return {"error": "Invalid state. 'ON' or 'OFF' only"}
    response: requests.Response = requests.get(f"{ESP_IP}/led/pattern?state={state.upper()}")
    return {"message": response.text}


@app.get("/led/{led}/{state}")
async def control_single_led(led: int, state: str) -> dict[str, str]:
    if led not in [1, 2, 3, 4, 5] or state.upper() not in ['ON', 'OFF']:
        return {"error": "Invalid LED or state."}
    response: requests.Response = requests.get(f"{ESP_IP}/led?led={led}&state={state.upper()}")
    return {"message": response.text}
