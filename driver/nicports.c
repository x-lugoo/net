//-------------------------------------------------------------------
//	nicports.c
//
//	This module creates a pseudo-file named '/proc/nicports' to
//	let users get the current values of RealTek 8139 registers.
//	(Be aware that, unlike most files in the '/proc' directory, 
//	this one contains raw binary data, not ascii characters, so
//	users should NOT attempt to view it with the 'cat' command!
//	In addition, each attempt to 'read()' this file begins from
//	the start of the file -- the 'f_pos' value remains at zero,
//	and file data is only returned in multiples of a longword.) 
//
//	NOTE: Written and tested using Linux kernel version 2.6.10.
//
//	programmer: ALLAN CRUSE
//	written on: 29 MAR 2005
//-------------------------------------------------------------------

#include <linux/module.h>	// for init_module() 
#include <linux/proc_fs.h>	// for create_proc_entry() 
#include <linux/pci.h>		// for pci_find_device()
#include <asm/uaccess.h>	// for put_user()

//#define VENDOR_ID  0x10EC	// RealTek Semiconductors Corp
//#define DEVICE_ID  0x8139	// RLT-8139 Network Controller
#define VENDOR_ID  0x1022
#define DEVICE_ID  0x2000

char modname[] = "nicports";
unsigned int iobase, io_len;


ssize_t my_read( struct file *file, char __user *buf, size_t len, loff_t *pos )
{
	int		i, datum;

	// sanity check: we cannot read beyond the final port-address
	if ( len > io_len ) len = io_len;
	else	len &= ~3;       // round downward to a multiple of 4 		

	// input each longword register-value and copy it into 'buf'
	for (i = 0; i < len; i+=4)
		{
		datum = inl( iobase + i );
		if ( copy_to_user( buf+i, &datum, 4 ) ) return -EFAULT;
		}		

	// return the total number of bytes that were stored in 'buf' 
	return	len;
}


struct file_operations my_fops = {
				owner: 	THIS_MODULE,
				read:	my_read,
				};
static int __devinit nicport_probe(struct pci_dev *dev, const struct pci_device_id *id){

	printk("start to  probe\n");
	return 0;
}

static struct pci_device_id nicport_table[] = {
	{ PCI_DEVICE(VENDOR_ID, DEVICE_ID) },
	{ },
};
static struct pci_driver nicport_driver = {
	.name = "jeff",
	.id_table = nicport_table,
	.probe = nicport_probe, 
};


int init_module( void )
{
	int ret;
/**
	struct pci_dev	*devp;
	struct proc_dir_entry	*entry;

	devp = pci_find_device( VENDOR_ID, DEVICE_ID, NULL );
	if ( !devp ) return -ENODEV;	
	iobase = pci_resource_start( devp, 0 );
	io_len = pci_resource_len( devp, 0 );
	printk( "RealTek 8139 Network Controller is present: " );
	printk( "iobase=%04X  io_len=%04X  \n", iobase, io_len );

	entry = create_proc_entry( modname, 0, NULL );
	entry->proc_fops = &my_fops;
*/
	printk("init nicport driver\n");
	ret = pci_register_driver(&nicport_driver);
	printk("pci_register_driver return ret=%d\n",ret);
	return ret;
}


void cleanup_module( void )
{
	pci_unregister_driver(&nicport_driver);
	
//	remove_proc_entry( modname, NULL );
}

MODULE_LICENSE("GPL"); 

