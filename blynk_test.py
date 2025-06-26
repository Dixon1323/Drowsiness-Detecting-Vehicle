import requests

blynk_api_url = "https://blr1.blynk.cloud/external/api/update?token=XYQlq2B7-f0_AfM_G6wPfrVJjrBa4rBw&v1="

custom_value = 42

full_url = f"{blynk_api_url}{custom_value}"

response = requests.get(full_url)

if response.status_code == 200:
    print(f"Value updated successfully to {custom_value}")
else:
    print(f"Failed to update value. Status code: {response.status_code}")
    print(response.text)
