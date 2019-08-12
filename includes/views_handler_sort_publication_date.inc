<?php

/**
 * @file
 * Definition of views_handler_sort_publication_date.
 */

/**
 * Sort handler for publication dates.
 *
 * This handler enables granularity, which is the ability to make dates
 * equivalent based upon nearness.
 *
 * @ingroup views_sort_handlers
 */
class views_handler_sort_publication_date extends views_handler_sort_date {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['null_date'] = array('default' => 'null');

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['null_date'] = array(
      '#type' => 'radios',
      '#title' => t('Treat empty publication date as'),
      '#options' => array(
        'null' => t('NULL'),
        'now' => t('Current time'),
        'created' => t('Content created date'),
        'changed' => t('Content last modified date'),
      ),
      '#description' => t('How should we treat content without a publication date?'),
      '#default_value' => $this->options['null_date'],
    );
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();

    if ($this->options['null_date'] == 'null') {
      $field_name = $this->real_field;
      $field = $this->table_alias . '.' . $field_name;
    }
    else {
      $field_name = $this->real_field . '_or_' . $this->options['null_date'];

      switch ($this->options['null_date']) {
        case 'now':
          $alt_value = REQUEST_TIME;
          break;

        case 'created':
          $alt_value = "node.created";
          break;

        case 'changed':
          $alt_value = "node.changed";
          break;
      }

      $field = "COALESCE($this->table_alias.$this->real_field, $alt_value)";
    }

    switch ($this->options['granularity']) {
      case 'second':
      default:
        $this->query->add_orderby(NULL, $field, $this->options['order'], $this->table_alias . '_' . $field_name);
        return;

      case 'minute':
        $formula = views_date_sql_format('YmdHi', $field);
        break;

      case 'hour':
        $formula = views_date_sql_format('YmdH', $field);
        break;

      case 'day':
        $formula = views_date_sql_format('Ymd', $field);
        break;

      case 'month':
        $formula = views_date_sql_format('Ym', $field);
        break;

      case 'year':
        $formula = views_date_sql_format('Y', $field);
        break;
    }

    // Add the field.
    $this->query->add_orderby(NULL, $formula, $this->options['order'], $this->table_alias . '_' . $field_name . '_' . $this->options['granularity']);
  }

}
