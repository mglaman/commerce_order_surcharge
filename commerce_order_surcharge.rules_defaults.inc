<?php

/**
 * @file
 * Default rules configurations for Order Surcharge.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_order_surcharge_default_rules_configuration() {
  $configs = array();
  $rule = '{ "rules_add_order_surcharge" : {
    "LABEL" : "Add Order Surcharge",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "commerce_order_surcharge", "entity" ],
    "ON" : [ "commerce_order_presave" ],
    "IF" : [
      { "NOT commerce_order_surcharge_exists" : { "commerce_order" : [ "commerce_order" ] } }
    ],
    "DO" : [
      { "commerce_order_surcharge_apply" : { "commerce_order" : [ "commerce_order" ] } }
    ]
  }
}';
  $configs['rules_add_order_surcharge'] = rules_import($rule);
  return $configs;
}
