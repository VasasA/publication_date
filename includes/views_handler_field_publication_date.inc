<?php

/**
 * @file
 * Definition of views_handler_field_publication_date.
 */

/**
 * A handler to provide proper displays for publication dates.
 *
 * This may be used on table fields that hold either UNIX timestamps or SQL
 * datetime strings.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_publication_date extends views_handler_field_date {

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
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();

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

    // Add the field.
    $this->field_alias = $this->query->add_field(NULL, $field, $this->table_alias . '_' . $field_name, $params);

    $this->add_additional_fields();
  }

}
