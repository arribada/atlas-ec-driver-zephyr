#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <oemec.h>

LOG_MODULE_REGISTER(simple_app);

const struct device * dev;

static int cmd_calib_clear(const struct shell *sh,
                           size_t argc, char **argv, void *data)
{
  int rc = sensor_attr_set(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY,SENSOR_ATTR_OEMEC_CALIBRATION_CLEAR,NULL);
  shell_print(sh,"Setting attribute for calibration clear - %d",rc);
  return rc;
}

static int cmd_calib_dry(const struct shell *sh,
                           size_t argc, char **argv, void *data)
{
  struct sensor_value calib = {};
  calib.val1 = atoi(argv[1]);
  int rc = sensor_attr_set(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY,SENSOR_ATTR_OEMEC_CALIBRATION_DRY,&calib);
  shell_print(sh,"Setting attribute for calibration dry - %d",rc);
  return 0;
}

static int cmd_calib_single(const struct shell *sh,
                         size_t argc, char **argv, void *data)
{
  struct sensor_value calib = {};
  calib.val1 = atoi(argv[1]);
  int rc = sensor_attr_set(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY,SENSOR_ATTR_OEMEC_CALIBRATION_SINGLE,&calib);
  shell_print(sh,"Setting attribute for calibration single - %d",rc);
  return 0;
}

static int cmd_calib_dual_low(const struct shell *sh,
                         size_t argc, char **argv, void *data)
{
  struct sensor_value calib = {};
  calib.val1 = atoi(argv[1]);
  int rc = sensor_attr_set(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY,SENSOR_ATTR_OEMEC_CALIBRATION_DUAL_LOW,&calib);
  shell_print(sh,"Setting attribute for calibration dual low - %d",rc);
  return 0;
}

static int cmd_calib_dual_high(const struct shell *sh,
                         size_t argc, char **argv, void *data)
{
  struct sensor_value calib = {};
  calib.val1 = atoi(argv[1]);
  int rc = sensor_attr_set(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY,SENSOR_ATTR_OEMEC_CALIBRATION_DUAL_HIGH,&calib);
  shell_print(sh,"Setting attribute for calibration dual high - %d",rc);
  return 0;
}
/* Creating subcommands (level 1 command) array for command "demo". */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_demo,
                               SHELL_CMD(clear, NULL, " Clear",
                                         cmd_calib_clear),
                               SHELL_CMD(dry,   NULL, " Dry", cmd_calib_dry),
                               SHELL_CMD(single,   NULL, " Single", cmd_calib_single),
                               SHELL_CMD(duallow,   NULL, " Low val of dual", cmd_calib_dual_low),
                               SHELL_CMD(dualhigh,   NULL, " High val of dual", cmd_calib_dual_high),
                               SHELL_SUBCMD_SET_END
                               );
/* Creating root (level 0) command "demo" */
SHELL_CMD_REGISTER(demo, &sub_demo, "Calib commands", NULL);



int main(void)
{
  int rc;
  LOG_INF("Running OEMEC simple app on %s\n", CONFIG_BOARD);
  dev = DEVICE_DT_GET_ANY(atlas_oemec);
  if (dev == NULL) {
    LOG_INF("No device found");
    return 0;
  }

  LOG_INF("Setting attributes");

  struct sensor_value probe = { // K=4.56
    .val1 = 456,
  };
  rc = sensor_attr_set(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY,SENSOR_ATTR_OEMEC_PROBE,&probe);
  LOG_INF("Set probe returned %d",rc);

  struct sensor_value conductivity;
  /* while (true) { */
  /*   rc = sensor_sample_fetch_chan(dev,SENSOR_CHAN_OEMEC_CONDUCTIVITY); */
  /*   if (rc != 0 ){ */
  /*           LOG_ERR("OEMEC failed: %d",rc); */
  /*     break; */
  /*   } */
  /*   else { // read channels */
  /*     rc = sensor_channel_get(dev, SENSOR_CHAN_OEMEC_CONDUCTIVITY, &conductivity); */
  /*           LOG_INF("Conductivity value %f", sensor_value_to_double(&conductivity)); */
  /*   } */
  /*   k_msleep(2000); */
  /* } */

  while(true){
    k_msleep(2000);
  }
  return 0;
}
