BOT_TOKEN = "949******"
CHAT_ID = "112215*****"

# Function to send a message to Telegram
def send_telegram_message(message):
    url = f"https://api.telegram.org/bot{BOT_TOKEN}/sendMessage"
    payload = {"chat_id": CHAT_ID, "text": message}
    response = requests.post(url, json=payload)
    if response.status_code == 200:
        print(f"Sent to Telegram: {message}")
    else:
        print(f" Failed to send message. Error: {response.text}")

# Read alerts from the log file and send to Telegram
with open("intrusion_log.txt", "r") as log_file:
    for line in log_file:
        send_telegram_message(line.strip())
