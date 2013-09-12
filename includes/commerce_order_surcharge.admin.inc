<?php
/**
 * @file
 * Administrative page callbacks for the commerce_order_surcharge module.
 */
/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function commerce_order_surcharge_settings_form($form_state) {
  $form['commerce_order_surcharge_display_title'] = array(
    '#type' => 'textfield',
    '#title' => 'Line Item Title',
    '#description' => t('How should this charge be displayed to the customer?'),
    '#default_value' => variable_get('commerce_order_surcharge_display_title'),
    '#required' => TRUE
  );
  $form['commerce_order_surcharge_amount'] = array(
    '#type' => 'textfield',
    '#title' => 'Surcharge Amount',
    '#description' => t('Type in a raw decimal amount to be added to each order: ex: 500 for $5.00'),
    '#default_value' => variable_get('commerce_order_surcharge_amount'),
    '#size' => 10,
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Validate handler: valiates the surcharge settings form.
 */
function commerce_order_surcharge_settings_form_validate($form, $form_state) {
  // Check for a valid postal code.
  $charge_amount = $form_state['values']['commerce_order_surcharge_amount'];
  if (!is_numeric($charge_amount)) {
    form_set_error('commerce_order_surcharge_amount', t('You must enter a numeric value'));
  }
}

