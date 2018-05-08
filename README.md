![c-sex-utils](static/logo.gif)

# c-sex-utils

some small C language tool functions

> MACROS

|  name   |   value    | belongs to function |
|----------|:---------:|-------------|
| CONNECTED |  1 | `get_connection_state` |
| DISCONNECTED | 0 | `get_connection_state` |
| OK | 1 | `get_mac_by_name` |
| NO | -1 | `get_mac_by_name` |
| SUCCESS | 1 | `http_get` `https_get` |
| FAILED | 0 | `http_get` `https_get` |


> FUNCTIONS

- get_mac_by_name
  - defination
    - `int get_mac_by_name(char *mac, char* if_name)`
  - params
    - mac **used to receive MAC addresses.**
    - if_name **the network card name**
  - return
    - OK
    - NO
  - example

```c
char mac_addr[12];
int is_success = get_mac_by_name(mac_addr, "eth0");
```

- get_connection_state
  - defination
    - `int get_connection_state(char *domain_name)`
  - params
    - domain_name **the domain name for ping.**
  - return
    - CONNECTED
    - DISCONNECTED
  - example

```c
int state = get_connection_state("www.baidu.com");
```

- http_get
  - defination
    - `int http_get(char *domain, char * url, int port, char * res, int res_len)`
  - params
    - domain **the domain name for request.**
    - url **the url for request.**
    - port **the port for request.**
    - res **the char[] for receiver response.**
    - res_len **the length of response.**
  - return
    - SUCCESS
    - FAILED
  - example

```c
int len = 4096;
char res[len];
int is_success = http_get("apistage.wenanle.com", "/", 80, res, len);
```

- https_get
  - defination
    - `int https_get(char *domain, char * url, int port, char * res, int res_len)`
  - params
    - domain **the domain name for request.**
    - url **the url for request.**
    - port **the port for request.**
    - res **the char[] for receiver response.**
    - res_len **the length of response.**
  - return
    - SUCCESS
    - FAILED
  - example

```c
int len = 4096;
char res[len];
int is_success = http_gets("api.wenanle.com", "/", 443, res, len);
```

- get_res_body
  - defination
    - `char* get_res_body(char* res)`
  - params
    - res **http or https response.**
  - return
    - **response body**
  - example

```c
char * body = get_res_body(res);
```
