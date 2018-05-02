# c-sex-utils

some small C language tool functions

> MACROS

|  name   |   value    |
|----------|:---------:|
| CONNECTED |  1 |
| DISCONNECTED | 0 |
| OK | 1 |
| NO | -1 |


> FUNCTIONS

- get_mac_by_name
  - defination
    - `int get_mac_by_name(char *mac)`
  - params
    - mac **used to receive MAC addresses.**
  - return
    - OK
    - NO
  - example

```c
char mac_addr[16];
int is_success = get_mac_by_name("eth0");
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
