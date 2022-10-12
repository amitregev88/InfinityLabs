#include <linux/posix_types.h>
#include <asm/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	 /*u16, u32*/
#include "ext2_fs.h" /**/
#include "../include/utility.h"

#define BASE_OFFSET 1024	  /* locates beginning of the super block (first group) */
#define FD_DEVICE "/dev/ram0" /* the floppy disk device */
#define SUCESS 0

static unsigned int block_size = 0; /* block size (to be calculated) */

/*struct ext2_super_block
/*{
/*	__u32 s_inodes_count;	   /* Inodes count */
/*	__u32 s_blocks_count;	   /* Blocks count */
/*	__u32 s_free_blocks_count; /* Free blocks count */
/*	__u32 s_free_inodes_count; /* Free inodes count */
/*	__u32 s_first_data_block;  /* First Data Block */
/*	__u32 s_log_block_size;	   /* Block size */
/*	__u32 s_blocks_per_group;  /* # Blocks per group */
/*	__u16 s_magic;			   /* Magic signature */
/*};

/*struct ext2_inode
/*{
/*	__u16 i_mode;				  /* File type and access rights */
/*	__u16 i_uid;				  /* Low 16 bits of Owner Uid */
/*	__u32 i_size;				  /* Size in bytes */
/*	__u32 i_atime;				  /* Access time */
/*	__u32 i_ctime;				  /* Creation time */
/*	__u32 i_mtime;				  /* Modification time */
/*	__u32 i_dtime;				  /* Deletion Time */
/*	__u16 i_gid;				  /* i_sizeBlocks count */
/*	__u32 i_flags;				  /* File flags */
/*	__u32 i_block[EXT2_N_BLOCKS]; /* Pointers to blocks */
/*};*/

/*struct ext2_group_desc
/*{
/*	__u32	bg_block_bitmap;	/* Blocks bitmap block */
/*	__u32	bg_inode_bitmap;	/* Inodes bitmap block */
/*	__u32	bg_inode_table;		/* Inodes table block */
/*	__u16	bg_free_blocks_count;	/* Free blocks count */
/*	__u16	bg_free_inodes_count;	/* Free inodes count */
/*	__u16	bg_used_dirs_count;	/* Directories count */
/*	__u16	bg_pad;
/*	__u32	bg_reserved[3];
/*};*/

int main(void)
{
	struct ext2_super_block super;
	struct ext2_group_desc group;
	int fd;

	/* open floppy device */

	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0)
	{
		perror(FD_DEVICE);
		exit(1); /* error while opening the floppy device */
	}

	/* read super-block */

	lseek(fd, BASE_OFFSET, SEEK_SET);
	read(fd, &super, sizeof(super));
	close(fd);

	if (super.s_magic != EXT2_SUPER_MAGIC)
	{
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}

	block_size = 1024 << super.s_log_block_size;

	printf("Reading super-block from device " FD_DEVICE ":\n"
		   "Inodes count            : %u\n"
		   "Blocks count            : %u\n"
		   "Reserved blocks count   : %u\n"
		   "Free blocks count       : %u\n"
		   "Free inodes count       : %u\n"
		   "First data block        : %u\n"
		   "Block size              : %u\n"
		   "Blocks per group        : %u\n"
		   "Inodes per group        : %u\n"
		   "Creator OS              : %u\n"
		   "First non-reserved inode: %u\n"
		   "Size of inode structure : %hu\n",
		   super.s_inodes_count,
		   super.s_blocks_count,
		   super.s_r_blocks_count, /* reserved blocks count */
		   super.s_free_blocks_count,
		   super.s_free_inodes_count,
		   super.s_first_data_block,
		   block_size,
		   super.s_blocks_per_group,
		   super.s_inodes_per_group,
		   super.s_creator_os,
		   super.s_first_ino, /* first non-reserved inode */
		   super.s_inode_size);

	lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
	read(fd, &group, sizeof(group));
	close(fd);

	printf("\nReading first group-descriptor from device " FD_DEVICE ":\n"
		   "Blocks bitmap block: %u\n"
		   "Inodes bitmap block: %u\n"
		   "Inodes table block : %u\n"
		   "Free blocks count  : %u\n"
		   "Free inodes count  : %u\n"
		   "Directories count  : %u\n",
		   group.bg_block_bitmap,
		   group.bg_inode_bitmap,
		   group.bg_inode_table,
		   group.bg_free_blocks_count,
		   group.bg_free_inodes_count,
		   group.bg_used_dirs_count); /* directories count */
}

/*void PrintSuperBlock(const char *virtual_device)
{
	struct ext2_super_block super;

	printf("Reading super-block from device %s :\n", virtual_device);
	printf(
		"Inodes count            : %u\n"
		"Blocks count            : %u\n"
		"Reserved blocks count   : %u\n"
		"Free blocks count       : %u\n"
		"Free inodes count       : %u\n"
		"First data block        : %u\n"
		"Block size              : %u\n"
		"Blocks per group        : %u\n"
		"Inodes per group        : %u\n"
		"Creator OS              : %u\n"
		"First non-reserved inode: %u\n"
		"Size of inode structure : %hu\n",
		super.s_inodes_count,
		super.s_blocks_count,
		super.s_r_blocks_count, /* reserved blocks count */
	/*	super.s_free_blocks_count,
		super.s_free_inodes_count,
		super.s_first_data_block,
		block_size,
		super.s_blocks_per_group,
		super.s_inodes_per_group,
		super.s_creator_os,
		super.s_first_ino, /* first non-reserved inode */
		/*super.s_inode_size);
}*/

/*oid PrintGroupDesc(const char *virtual_device)
{
	struct ext2_group_desc group;

	printf("Reading first group-descriptor from device %s :\n", virtual_device);
	printf(
		   "Blocks bitmap block: %u\n"
		   "Inodes bitmap block: %u\n"
		   "Inodes table block : %u\n"
		   "Free blocks count  : %u\n"
		   "Free inodes count  : %u\n"
		   "Directories count  : %u\n",
		   group.bg_block_bitmap,
		   group.bg_inode_bitmap,
		   group.bg_inode_table,
		   group.bg_free_blocks_count,
		   group.bg_free_inodes_count,
		   group.bg_used_dirs_count); /* directories count */
/*}
/*
int OpenDevice()
{
	int fd;
	int status = 0;

	/* open floppy device */

/*	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0)
	{
		perror(FD_DEVICE);
		exit(1); /* error while opening the floppy device */
	/*}

	/* read super-block */

/*	status = lseek(fd, BASE_OFFSET, SEEK_SET);
	ReturnErnoIfFail(status, "lseek () failed", status);
	status = read(fd, &super, sizeof(super));
	ReturnErnoIfFail(status, "read() failed", status);
	status = close(fd);
	ReturnErnoIfFail(status, "close failed", status);

	if (super.s_magic != EXT2_SUPER_MAGIC)
	{
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}

	block_size = 1024 << super.s_log_block_size;

	return SUCESS;
}*/
