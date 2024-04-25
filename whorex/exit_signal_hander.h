#pragma once
#include "user.h"
#include "complex_buffer.h"
#include "tui/login_page.h"

static struct user session_user;
static complex_buffer_t history_buffer;
static login_result_t result;

static WINDOW* main_window;

void exit_signal_handler(int signo);