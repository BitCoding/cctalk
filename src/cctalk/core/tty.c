/**
 * Copyright (c) 2016 BitCoding
 */
#include <cctalk/core/tty.h>

#include <poll.h>
#include <unistd.h>
#include <termios.h>

static int setup_serial_line(int fd)
{
	struct termios tio = {0};

	cfmakeraw(&tio);
	cfsetspeed(&tio, B9600);

	if (-1 == tcsetattr(fd, TCSANOW, &tio))
		return -1;

	if (-1 == tcflush(fd, TCIOFLUSH))
		return -1;

	return 0;
}

static int open_tty(struct cctalk_tty *tty,const char *path)
{
  
  if (-1 == (tty->fd = open(path, O_RDWR | O_NOCTTY)))
      return -1;

  if (-1 == setup_serial_line(tty->fd))
	  return -1;
  
  return 0;
}

struct cctalk_tty* new_cctalk_tty(const char *path,int timeout){
  struct cctalk_tty *tty;
  tty = malloc(sizeof(*tty));
  tty->timeout = timeout;
  
  if(-1 == open_tty(tty,path)){
    free(tty);
    return 0;
  }
    
  return tty;
}

ssize_t write_cctalk_tty(struct cctalk_tty* tty,const void *buf, size_t count)
{
	struct pollfd pfd = {tty->fd, POLLOUT, 0};
	size_t total = 0;

	while (total < count) {
		if (1 != poll(&pfd, 1, tty->timeout))
			return -1;

		ssize_t written = write(tty->fd, buf + total, count - total);

		if (written < 1)
			return -1;

		total += written;
	}

	return total;
}

ssize_t read_cctalk_tty(struct cctalk_tty* tty, void *buf, size_t count)
{
	struct pollfd pfd = {tty->fd, POLLIN, 0};
	size_t total = 0;

	while (total < count) {
		if (1 != poll(&pfd, 1, tty->timeout))
			return -1;

		ssize_t rread = read(tty->fd, buf + total, count - total);

		if (rread < 1)
			return -1;

		total += rread;
	}

	return total;
}

void destroy_cctalk_tty(struct cctalk_tty* tty)
{
  if (NULL == tty)
    return;

  close(tty->fd);
  free(tty);
  tty = 0;
}
