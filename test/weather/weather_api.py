import requests

# # Make an API call and store the response.
# url = 'https://passport.bilibili.com/web/captcha/combine?plat=6'
# # headers = {'Accept': 'application/vnd.github.v3+json'}
# # r = requests.get(url, headers=headers)
# r = requests.get(url)
# # print(f"Status code: {r.code}")
# print(f"Status code: {r.status_code}")

# response_dict = r.json()
# print(f"Code: {response_dict['code']}")
# print(f"Success: {response_dict['data']['result']['success']}")
# print(f"Gt: {response_dict['data']['result']['gt']}")
# print(f"Challenge: {response_dict['data']['result']['challenge']}")
# print(f"Key: {response_dict['data']['result']['key']}")

# Make an API call and store the response.
url = 'https://restapi.amap.com/v3/weather/weatherInfo?city=110101&key=ced23a214c9021de0491f71f45&extensions=all' # fake API key
# urla = "https://jsonplaceholder.typicode.com/posts/1"
# headers = {'Accept': 'application/vnd.github.v3+json'}
# r = requests.get(url, headers=headers)
# r = requests.get(url)

response = requests.get(url)

response_json = response.json()

# print(response_json)

print(response_json['status']) # print data

print('\n')

forecasts = response_json['forecasts']



# print(f"Status code: {r.status_code}")

# response_dict = r.json()
# print(f"Code: {response_dict['code']}")
# print(f"Status: {response_dict['status']}")
# print(f"Ts: {response_dict['ts']}")
# print(f"Url: {response_dict['data']['url']}")
# print(f"Oauthkey: {response_dict['data']['oauthKey']}")
