
static int __init s3c2410ts_probe(struct device *dev)
{
register_device(&ts.dev);
ioremap();	
}

static int s3c2410ts_remove(struct device *dev)
{
	
	input_unregister_device(&ts.dev);
	iounmap(base_addr);

}

static struct device_driver s3c2410ts_driver = {
       .name           = "s3c2410-ts",
       .bus            = &platform_bus_type,
       .probe          = s3c2410ts_probe,
       .remove         = s3c2410ts_remove,
};


int __init s3c2410ts_init(void)
{
	return driver_register(&s3c2410ts_driver);
}

void __exit s3c2410ts_exit(void)
{
	driver_unregister(&s3c2410ts_driver);
}

module_init(s3c2410ts_init);
module_exit(s3c2410ts_exit);
