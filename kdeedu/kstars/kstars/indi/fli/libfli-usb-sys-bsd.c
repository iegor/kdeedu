/*

  Copyright (c) 2002 Finger Lakes Instrumentation (FLI), L.L.C.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

        Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

        Redistributions in binary form must reproduce the above
        copyright notice, this list of conditions and the following
        disclaimer in the documentation and/or other materials
        provided with the distribution.

        Neither the name of Finger Lakes Instrumentation (FLI), LLC
        nor the names of its contributors may be used to endorse or
        promote products derived from this software without specific
        prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

  ======================================================================

  Finger Lakes Instrumentation, L.L.C. (FLI)
  web: http://www.fli-cam.com
  email: support@fli-cam.com

*/

#include <sys/types.h>
#include <dev/usb/usb.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <errno.h>

#include "libfli-libfli.h"
#include "libfli-sys.h"
#include "libfli-usb.h"

long unix_usbverifydescriptor(flidev_t dev, fli_unixio_t *io)
{
  usb_device_descriptor_t usb_desc;
  int r;
  
  if ((r = read(io->fd, &usb_desc, sizeof(usb_device_descriptor_t))) !=
      sizeof(usb_device_descriptor_t))
  {
    debug(FLIDEBUG_FAIL, "linux_usbverifydescriptor(): Could not read descriptor.");
    return -EIO;
  }
  else
  {
    debug(FLIDEBUG_INFO, "USB device descriptor:");
    if(usb_desc.idVendor != 0x0f18)
    {
      debug(FLIDEBUG_FAIL, "linux_usbverifydescriptor(): Not a FLI device!");
      return -ENODEV;
    }
    
    switch(DEVICE->domain)
    {
     case FLIDOMAIN_USB:
      if(usb_desc.idProduct != 0x0002)
      {
	return -ENODEV;
      }
      break;
      
     default:
      return -EINVAL;
      break;
    }
        
    DEVICE->devinfo.fwrev = usb_desc.bcdDevice;
  }
    
  return 0;
}

long bsd_bulkwrite(flidev_t dev, void *buf, long *wlen)
{
  fli_unixio_t *io;
  long org_wlen = *wlen;
  int to;

  io = DEVICE->io_data;
  to = DEVICE->io_timeout;

  if (ioctl(io->fd, USB_SET_TIMEOUT, &to) == -1)
    return -errno;

  *wlen = write(io->fd, buf, *wlen);

  if (*wlen != org_wlen)
    return -errno;
  else
    return 0;
}

long bsd_bulkread(flidev_t dev, void *buf, long *rlen)
{
  fli_unixio_t *io;
  long org_rlen = *rlen;
  int to;

  io = DEVICE->io_data;
  to = DEVICE->io_timeout;

  if (ioctl(io->fd, USB_SET_TIMEOUT, &to) == -1)
    return -errno;

  *rlen = read(io->fd, buf, *rlen);

  if (*rlen != org_rlen)
    return -errno;
  else
    return 0;
}
