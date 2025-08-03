#pragma once

bool net_init_client(const char* server_ip, int port);
void net_send_input(char input);
int net_receive_state(char* buffer, int bufferSize);
void net_cleanup();

