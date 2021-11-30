<?php

/**
 * @file
 * Publication date administration forms.
 */

/**
 * Publication date administration page for calback.
 */
function publication_date_admin_form($form, &$form_state) {
  // Publication Date Popup Configuration.
  $config = config('publication_date.settings');
  $form['#config'] = 'publication_date.settings';
  $form['popup_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date Popup Configuration'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['popup_config']['publication_date_popup_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use date popup field'),
    '#default_value' => $config->get('publication_date_popup_enable'),
  );
  $form['popup_config']['publication_date_popup_year_start'] = array(
    '#type' => 'number',
    '#title' => t('Starting year'),
    '#default_value' => $config->get('publication_date_popup_year_start'),
    '#field_prefix' => '-',
    '#field_suffix' => 'years from now',
    '#maxlength' => 10,
    '#size' => 3,
    '#min' => 0,
  );
  $form['popup_config']['publication_date_popup_year_end'] = array(
    '#type' => 'number',
    '#title' => t('Ending year'),
    '#default_value' => $config->get('publication_date_popup_year_end'),
    '#field_prefix' => '+',
    '#field_suffix' => 'years from now',
    '#maxlength' => 10,
    '#size' => 3,
    '#min' => 0,
  );

  return system_settings_form($form);
}
