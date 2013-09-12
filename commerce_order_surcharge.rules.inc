<?php

/**
 * @file
 * Rules integration for order surcharge.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_condition_info().
 */
function commerce_order_surcharge_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_order_surcharge_exists'] = array(
    'label' => t('Surcharge line item exists'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'description' => t('The order whose line items should be checked for an existing shipping line item.'),
      ),
    ),
    'group' => t('Commerce Order Surcharge'),
    'callbacks' => array(
      'execute' => 'commerce_order_surcharge_line_item_exists',
    ),
  );

  return $conditions;
}

/**
 * Checks an order for the existence of an order surcharge line item.
 *
 * @param $order
 *   The order to check for an order surcharge line item.
 */
function commerce_order_surcharge_line_item_exists($order, $service) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

  // Loop over all the line items on the order.
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    // If the current line item is an order surcharge line item and the condition either
    if ($line_item_wrapper->type->value() == 'commerce_order_surcharge' ) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_order_surcharge_rules_action_info() {
  $actions = array();
  $actions['commerce_order_surcharge_apply'] = array(
    'label' => t('Apply surcharge to an order'),
      'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order'),
        'save' => TRUE,
      ),
    ),
    'group' => t('Commerce Order Surcharge'),
  );

  return $actions;
}

function commerce_order_surcharge_apply($order) {
  //@todo: Should check if order has line item already since rule can be modified.
  $line_item = commerce_order_surcharge_line_item_new($order->order_id);

  // Save and add the line item to the order.
  commerce_order_surcharge_add_surcharge_line_item($line_item, $order, TRUE);
}
/**
 * @}
 */
