#pragma once

#define LOGIN "POST /goform/formLogin HTTP/1.1\r\n" \
    "Host: %s\r\n" \
	"Connection: keep-alive\r\n" \
	"Content-Length: 68\r\n" \
	"Cache-Control: max-age=0\r\n" \
	"Origin: http ://%s\r\n" \
	"Upgrade-Insecure-Requests: 1\r\n" \
	"Content-Type: application/x-www-form-urlencoded\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n" \
	"Accept: text/html, application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n" \
	"Referer: http://%s/login_new.asp\r\n" \
	"Accept-Encoding: gzip, deflate\r\n" \
	"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n" \
	"pwd=password&login_button.x=44&login_button.y=12&err_flag=0&err_msg="

#define LOGIN_COOKIE "POST /goform/formLogin HTTP/1.1\r\n" \
    "Host: %s\r\n" \
	"Connection: keep-alive\r\n" \
	"Content-Length: 68\r\n" \
	"Cache-Control: max-age=0\r\n" \
	"Origin: http ://%s\r\n" \
	"Upgrade-Insecure-Requests: 1\r\n" \
	"Content-Type: application/x-www-form-urlencoded\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n" \
	"Accept: text/html, application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n" \
	"Referer: http://%s/login_new.asp\r\n" \
	"Accept-Encoding: gzip, deflate\r\n" \
	"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n" \
	"Cookie: SID=%s\r\n\r\n" \
	"pwd=password&login_button.x=44&login_button.y=12&err_flag=0&err_msg="

#define LOGOUT "POST /goform/formLogout HTTP/1.1\r\n" \
    "Host: %s\r\n" \
	"Connection: keep-alive\r\n" \
	"Content-Length: 10\r\n" \
	"Cache-Control: max-age=0\r\n" \
	"Origin: http ://%s\r\n" \
	"Upgrade-Insecure-Requests: 1\r\n" \
	"Content-Type: application/x-www-form-urlencoded\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n" \
	"Accept: text/html, application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n" \
	"Referer: http://%s/login_new.asp\r\n" \
	"Accept-Encoding: gzip, deflate\r\n" \
	"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n" \
	"Cookie: SID=%s\r\n\r\n" \
	"sessionID="

#define ACCEPT "GET /accept.asp HTTP/1.1\r\n" \
	"Host: %s\r\n" \
	"Connection: keep-alive\r\n" \
	"Upgrade-Insecure-Requests: 1\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n" \
	"Accept: text/html, application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n" \
	"Referer: http://%s/goform/formLogin\r\n" \
	"Accept-Encoding: gzip, deflate\r\n" \
	"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n"

#define ACCEPT_COOKIE "GET /accept.asp HTTP/1.1\r\n" \
	"Host: %s\r\n" \
	"Connection: keep-alive\r\n" \
	"Upgrade-Insecure-Requests: 1\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n" \
	"Accept: text/html, application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n" \
	"Referer: http://%s/goform/formLogin\r\n" \
	"Accept-Encoding: gzip, deflate\r\n" \
	"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n" \
	"Cookie: SID=%s\r\n\r\n"

#define PORT_CONTROL "POST /goform/formSetPoePortCfg HTTP/1.1\r\n" \
	"Host: %s\r\n" \
	"Connection: keep-alive\r\n" \
	"Content-Length: %d\r\n" \
	"Cache-Control: max-age = 0\r\n" \
	"Origin: http://%s\r\n" \
	"Upgrade-Insecure-Requests: 1\r\n" \
	"Content-Type: application/x-www-form-urlencoded\r\n" \
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n" \
	"Accept: text/html, application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n" \
	"Referer: http://%s/base/poe_port_cfg.asp\r\n" \
	"Accept-Encoding: gzip, deflate\r\n" \
	"Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n" \
	"Cookie: SID=%s\r\n\r\n" \
	"%s"

#define PORT_CONTROL_CONTENT \
	"unit_no=1&java_port=0&applet_port=&applet_unit=&dbgopt=0&inputBox_interface1=&poeAdminMode=%d&poePriority=1&highPowMode=4&poeDetectionMode=3&poe_timer_ctrl_list=26&poePowerLimitType=4&poePowerLimit=30000&CBox_1=%d&inputBox_interface1=&err_flag=0&err_msg=&multiple_ports=0&selectedPorts=g%d%%3B&submt=16&refrsh=&click_sched=&sched_id="
